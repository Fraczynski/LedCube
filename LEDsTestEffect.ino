void testLEDs() {
  if (loading) {
    clearCube();
    i = 0;
    j = 0;
    k = 0;
    loading = false;
  }
  timer++;
  if (timer > TEST_LEDS_TIME) {
    timer = 0;
    clearVoxel(i, j, k);
    if (i == 8) {
      i = 0;
      k++;
    }
    if (k == 8) {
      j++;
      k = 0;
    }
    if (j == 8) {
      j = 0;
    }
    setVoxel(i, j, k);
    i++;
  }
}
