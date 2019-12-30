void drawCube(uint8_t voxelsArray[8][8], uint8_t x, uint8_t y, uint8_t z, uint8_t s) {
  for (uint8_t i = 0; i < s; i++) {
    setVoxel(voxelsArray, x, y + i, z);
    setVoxel(voxelsArray, x + i, y, z);
    setVoxel(voxelsArray, x, y, z + i);
    setVoxel(voxelsArray, x + s - 1, y + i, z + s - 1);
    setVoxel(voxelsArray, x + i, y + s - 1, z + s - 1);
    setVoxel(voxelsArray, x + s - 1, y + s - 1, z + i);
    setVoxel(voxelsArray, x + s - 1, y + i, z);
    setVoxel(voxelsArray, x, y + i, z + s - 1);
    setVoxel(voxelsArray, x + i, y + s - 1, z);
    setVoxel(voxelsArray, x + i, y, z + s - 1);
    setVoxel(voxelsArray, x + s - 1, y, z + i);
    setVoxel(voxelsArray, x, y + s - 1, z + i);
  }
}

void drawCube(uint8_t x, uint8_t y, uint8_t z, uint8_t s) {
  drawCube(cube, x, y, z, s);
}
