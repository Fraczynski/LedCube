void stroboscope() {
  if (loading) {
    clearCube();
    loading = false;
    currentEffectTime = timeScale * STROBOSCOPE_TIME;
  }
  timer++;
  if (timer > currentEffectTime) {
    timer = 0;
    clearCube();
    for (int i = 0; i < 15; i++) {
      selX = random(0, 8);
      selY = random(0, 8);
      selZ = random(0, 8);
        setVoxel(selX, selY, selZ);
    }
  }
}
