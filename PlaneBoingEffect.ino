uint8_t planePosition = 0;
uint8_t planeDirection = 0;
bool looped = false;

void planeBoing() {
  if (loading) {
    clearCube();
    uint8_t axis = random(0, 3);
    planePosition = random(0, 2) * 7;
    setLayer(axis, planePosition);
    if (axis == X_axis) {
      if (planePosition == 0) {
        planeDirection = POSITION_X;
      } else {
        planeDirection = NEG_X;
      }
    } else if (axis == Y_axis) {
      if (planePosition == 0) {
        planeDirection = POSITION_Y;
      } else {
        planeDirection = NEG_Y;
      }
    } else if (axis == Z_axis) {
      if (planePosition == 0) {
        planeDirection = POSITION_Z;
      } else {
        planeDirection = NEG_Z;
      }
    }
    timer = 0;
    looped = false;
    loading = false;
    currentEffectOriginalTime = PLANE_BOING_TIME;
    currentEffectTime = currentEffectOriginalTime * timeScale;
  }

  timer++;
  if (timer > currentEffectTime) {
    timer = 0;
    shift(planeDirection);
    if (planeDirection % 2 == 0) {
      planePosition++;
      if (planePosition == 7) {
        if (looped) {
          loading = true;
        } else {
          planeDirection++;
          looped = true;
        }
      }
    } else {
      planePosition--;
      if (planePosition == 0) {
        if (looped) {
          loading = true;
        } else {
          planeDirection--;
          looped = true;
        }
      }
    }
  }
}
