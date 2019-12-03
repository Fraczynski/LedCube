void testLayers() {
  if (loading) {
    clearCube();
    j = 0;
    loading = false;
  }
  timer++;
  if (timer > TEST_LAYERS_TIME) {
    timer = 0;
    clearCube();
    for (int i = 0; i < 8; i++) {
      for (int k = 0; k < 8; k++) {
        setVoxel(i, j, k);
      }
    }
    j = j < 8 ? j + 1 : 0;
  }
}
