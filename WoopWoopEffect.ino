void woopWoop() {
  if (loading) {
    clearCube();
    cubeSize = 2;
    cubeExpanding = true;
    loading = false;
    currentEffectOriginalTime = WOOP_WOOP_TIME;
    currentEffectTime = currentEffectOriginalTime * timeScale;
  }

  timer++;
  if (timer > currentEffectTime) {
    timer = 0;
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
