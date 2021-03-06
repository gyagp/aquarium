//
// Copyright (c) 2019 The Aquarium Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

#include "ContextFactory.h"

#include "Aquarium.h"
#include "opengl/ContextGL.h"
#ifdef ENABLE_DAWN_BACKEND
#include "dawn/ContextDawn.h"
#endif
#ifdef ENABLE_D3D12_BACKEND
#include "d3d12/ContextD3D12.h"
#endif

ContextFactory::ContextFactory() : mContext(nullptr) {
}

ContextFactory::~ContextFactory() {
  delete mContext;
}

Context *ContextFactory::createContext(BACKENDTYPE backendType) {
  if (backendType & BACKENDTYPE::BACKENDTYPEANGLE) {
#if defined(ENABLE_ANGLE_BACKEND)
    mContext = ContextGL::create(backendType);
#endif
  } else if (backendType & BACKENDTYPE::BACKENDTYPEDAWN) {
#if defined(ENABLE_DAWN_BACKEND)
      mContext = ContextDawn::create(backendType);
#endif
  } else if (backendType & BACKENDTYPE::BACKENDTYPED3D12) {
#if defined(ENABLE_D3D12_BACKEND)
      mContext = ContextD3D12::create(backendType);
#endif
  } else if (backendType & BACKENDTYPE::BACKENDTYPEOPENGL) {
#if defined(ENABLE_OPENGL_BACKEND)
    mContext = ContextGL::create(backendType);
#endif
  }
  return mContext;
}
