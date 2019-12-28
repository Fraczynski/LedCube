void testLayers() {
  if (loading) {
    clearCube();
    j = 0;
    loading = false;
    currentEffectTime = timeScale * TEST_LAYERS_TIME;
  }
  timer++;
  if (timer > currentEffectTime) {
    timer = 0;
    clearCube();
    for (uint8_t i = 0; i < 8; i++) {
      for (uint8_t k = 0; k < 8; k++) {
        setVoxel(i, j, k);
      }
    }
    j++;
    if(j >= 8){
      j = 0;
    }
  }
}
