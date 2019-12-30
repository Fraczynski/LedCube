bool sending = false;
bool exploded = false;
uint8_t gravitationTime = 0;
uint8_t explodeTime = 0;
uint8_t relay = 0;

uint8_t tmpCube[8][8];

void fireworks() {
  if (loading) {
    clearCube();
    loading = false;
    sending = false;
    exploded = false;
    gravitationTime = 0;
    explodeTime = 0;
    currentEffectTime = timeScale * FIREWORKS_TIME;
  }

  timer++;
  if (timer > currentEffectTime) {
    timer = 0;
    if (!sending && !exploded) {
      clearCube();
      selX = random(0, 4) + 2;
      selZ = random(0, 4) + 2;
      selY = 0;
      sending = true;
    }
    else if (exploded) {
        uint8_t newX = 0;
        uint8_t newY = 0;
        uint8_t newZ = 0;
        explodeTime++;
        if (explodeTime > 3) {
          if (relay == 2) {
            shift(tmpCube, NEG_Y);
            selY--;
            relay = 0;
          }
          relay++;
        }
        else {
          for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
              for (int k = 0; k < 8; k++) {
                if (getVoxel(i, j, k)) {
                  if (explodeTime > 3) {
                    clearVoxel(tmpCube, i, j, k);
                  }
                  if (i < selX) {
                    newX = i - ((explodeTime < 4) ? random(0, 2) : 0);
                  }
                  else {
                    newX = i + ((explodeTime < 4) ? random(0, 2) : 0);
                  }
                  if (j < selY) {
                    newY = j - random(0, 2);
                  }
                  else {
                    if (explodeTime < 3) {
                      uint8_t tmp = random(0, 8);
                      newY = j + ((tmp < 2) ? tmp : 0);
                    }
                  }
                  if (k < selZ) {
                    newZ = k - ((explodeTime < 4) ? random(0, 2) : 0);
                  }
                  else {
                    newZ = k + ((explodeTime < 4) ? random(0, 2) : 0);
                  }
                  if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8 && newZ >= 0 && newZ < 8) {
                    setVoxel(tmpCube, newX, newY, newZ);
                  }

                }
              }
            }
          }
        }
        copyCube(tmpCube, cube);
          if (explodeTime == 26) {
            sending = false;
            loading = true;
          }
      }
    else {
      selY++;
      setVoxel(selX, selY, selZ);
      clearVoxel(selX, selY - 1, selZ);
      if (selY == 5) {
        sending = false;
        exploded = true;
        drawCube(selX - 1, selY - 1, selZ - 1, 3);
      }
    }
  }
}
