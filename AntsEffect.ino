void ants() {
  if (loading) {
    clearCube();
    loading = false;
    currentEffectOriginalTime = ANTS_TIME;
    currentEffectTime = currentEffectOriginalTime * timeScale;
  }
  timer++;
  if (timer > currentEffectTime) {
    timer = 0;
    for (int i = 0; i < 20; i++) {
      selX = random(0, 8);
      selY = random(0, 8);
      selZ = random(0, 8);
      if (!getVoxel(selX, selY, selZ)) {
        setVoxel(selX, selY, selZ);
      }
      else{
          clearVoxel(selX, selY, selZ);
      }
    }
  }
}
