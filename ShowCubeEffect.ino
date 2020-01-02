uint8_t frame = 0;

void showCube() {
  if (loading) {
    clearCube();
    loading = false;
    currentEffectTime = timeScale * SHOW_CUBE_TIME;
    frame = 0;
    cubeSize = 8;
    cubeExpanding = false;
  }
  timer++;
  if (timer > currentEffectTime) {
    timer = 0;
    if (frame < 8) {
      setVoxel(frame, 0, 0);
      setVoxel(0, frame, 0);
      setVoxel(0, 0, frame);
    }
    else if (frame < 16) {
      setVoxel(frame % 8, 7, 0);
      setVoxel(0, 7, frame % 8);

      setVoxel(7, frame % 8, 0);
      setVoxel(7, 0, frame % 8);

      setVoxel(frame % 8, 0, 7);
      setVoxel(0, frame % 8, 7);
    }
    else if (frame < 24) {
      setVoxel(7, 7, frame % 8);
      setVoxel(frame % 8, 7, 7);
      setVoxel(7, frame % 8, 7);
    }
    else if (frame < 40) {
      if (frame % 2 == 0 && frame != 24 && frame != 38) {
        if (cubeExpanding) {
          cubeSize += 2;
          if (cubeSize == 8) {
            cubeExpanding = false;
          }
        } else {
          cubeSize -= 2;
          if (cubeSize == 2) {
            cubeExpanding = true;
          }
        }
        clearCube();
        drawCube(4 - cubeSize / 2, 4 - cubeSize / 2, 4 - cubeSize / 2, cubeSize);
      }
    }
    else if (frame < 48) {
      clearVoxel(frame % 8, 0, 0);
      clearVoxel(0, frame % 8, 0);
      clearVoxel(0, 0, frame % 8);
    }
    else if (frame < 56) {
      clearVoxel(frame % 8, 7, 0);
      clearVoxel(0, 7, frame % 8);

      clearVoxel(7, frame % 8, 0);
      clearVoxel(7, 0, frame % 8);

      clearVoxel(frame % 8, 0, 7);
      clearVoxel(0, frame % 8, 7);
    }
    else if (frame < 64) {
      clearVoxel(7, 7, frame % 8);
      clearVoxel(frame % 8, 7, 7);
      clearVoxel(7, frame % 8, 7);
    }
    else if (frame >= 66) {
      loading = true;
    }
    frame++;
  }
}
