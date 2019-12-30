void shift(uint8_t voxelsArray[8][8], uint8_t dir) {

  if (dir == POSITION_X) {
    for (uint8_t y = 0; y < 8; y++) {
      for (uint8_t z = 0; z < 8; z++) {
        voxelsArray[y][z] = voxelsArray[y][z] << 1;
      }
    }
  } else if (dir == NEG_X) {
    for (uint8_t y = 0; y < 8; y++) {
      for (uint8_t z = 0; z < 8; z++) {
        voxelsArray[y][z] = voxelsArray[y][z] >> 1;
      }
    }
  } else if (dir == POSITION_Y) {
    for (uint8_t y = 1; y < 8; y++) {
      for (uint8_t z = 0; z < 8; z++) {
        voxelsArray[y - 1][z] = voxelsArray[y][z];
      }
    }
    for (uint8_t i = 0; i < 8; i++) {
      voxelsArray[7][i] = 0;
    }
  } else if (dir == NEG_Y) {
    for (uint8_t y = 7; y > 0; y--) {
      for (uint8_t z = 0; z < 8; z++) {
        voxelsArray[y][z] = voxelsArray[y - 1][z];
      }
    }
    for (uint8_t i = 0; i < 8; i++) {
      voxelsArray[0][i] = 0;
    }
  } else if (dir == POSITION_Z) {
    for (uint8_t y = 0; y < 8; y++) {
      for (uint8_t z = 1; z < 8; z++) {
        voxelsArray[y][z - 1] = voxelsArray[y][z];
      }
    }
    for (uint8_t i = 0; i < 8; i++) {
      voxelsArray[i][7] = 0;
    }
  } else if (dir == NEG_Z) {
    for (uint8_t y = 0; y < 8; y++) {
      for (uint8_t z = 7; z > 0; z--) {
        voxelsArray[y][z] = voxelsArray[y][z - 1];
      }
    }
    for (uint8_t i = 0; i < 8; i++) {
      voxelsArray[i][0] = 0;
    }
  }
}

void shift(uint8_t dir) {
  shift(cube, dir);
}

void shiftVoxel(uint8_t dir, uint8_t x, uint8_t y, uint8_t z) {

  if (dir == POSITION_X) {
    if(getVoxel(cube, x, y, z)){
      setVoxel(cube, x + 1, y, z);
    }
    else{
      clearVoxel(cube, x + 1, y, z);
    }
    clearVoxel(cube, x, y, z);
  }
  else if (dir == NEG_X) {
    if(getVoxel(cube, x, y, z)){
      setVoxel(cube, x - 1, y, z);
    }
    else{
      clearVoxel(cube, x - 1, y, z);
    }
    clearVoxel(cube, x, y, z);
  }
  else if (dir == POSITION_Y) {
    if(getVoxel(cube, x, y, z)){
      setVoxel(cube, x, y + 1, z);
    }
    else{
      clearVoxel(cube, x, y + 1, z);
    }
    clearVoxel(cube, x, y, z);
  }
  else if (dir == NEG_Y) {
    if(getVoxel(cube, x, y, z)){
      setVoxel(cube, x, y - 1, z);
    }
    else{
      clearVoxel(cube, x, y - 1, z);
    }
    clearVoxel(cube, x, y, z);
  }
  else if (dir == POSITION_Z) {
    if(getVoxel(cube, x, y, z)){
      setVoxel(cube, x, y, z + 1);
    }
    else{
      clearVoxel(cube, x, y, z + 1);
    }
    clearVoxel(cube, x, y, z);
  }
  else if (dir == NEG_Z) {
    if(getVoxel(cube, x, y, z)){
      setVoxel(cube, x, y, z - 1);
    }
    else{
      clearVoxel(cube, x, y, z - 1);
    }
    clearVoxel(cube, x, y, z);
  }
}
