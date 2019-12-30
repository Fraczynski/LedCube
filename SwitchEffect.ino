void switchEffect() {
  if (currentEffect.equals(TEST_LAYERS)) {    testLayers();  }
  else if (currentEffect.equals(LIGHT)) {    lightCube();    currentEffect = STATIC_EFFECT;  }
  else if (currentEffect.equals(CLEAR)) {    clearCube();    currentEffect = STATIC_EFFECT;  }
  else if (currentEffect.equals(RAIN)){    rain();  }
  else if (currentEffect.equals(PLANE_BOING)){    planeBoing();  }
  else if (currentEffect.equals(SEND_VOXELS)){    sendVoxels();  }
  else if (currentEffect.equals(WOOP_WOOP)){    woopWoop();  }
  else if (currentEffect.equals(CUBE_JUMP)){    cubeJump();  }
  else if (currentEffect.equals(GLOW)){    glow();  }
  else if (currentEffect.equals(TEXT)){    text(textToDisplay);  }
  else if (currentEffect.equals(FIREWORKS)){    fireworks();  }
  else if (currentEffect.equals(STROBOSCOPE)){    stroboscope();  }
  else if (currentEffect.equals(ANTS)){    ants();  }
  else if (currentEffect.equals(AXIS_UPDOWN_RANDSUSPEND)){    axisUpdownRandsuspend();  }
  else if (!currentEffect.equals(STATIC_EFFECT)){    currentEffect = LIGHT;  }
  renderCube();
}
