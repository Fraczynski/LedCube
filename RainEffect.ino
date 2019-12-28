void rain() {
  if (loading) {
    clearCube();
    loading = false;
    currentEffectTime = timeScale * RAIN_TIME;
  }
  timer++;
  if (timer > currentEffectTime) {
    timer = 0;
    shift(NEG_Y);
    uint8_t numDrops = random(0, 5);
    for (uint8_t i = 0; i < numDrops; i++) {
      setVoxel(random(0, 8), 7, random(0, 8));
    }
  }
}
