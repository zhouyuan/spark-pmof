/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <libpmem.h>
#include <fcntl.h> 
#include <unistd.h>
#include <cstring>
#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <cassert>
#include <stdexcept>
#include "com_intel_pmdevice.h"

int fd = -1;
uint64_t size = 0;
char *addr = NULL;

// copied form openjdk: http://hg.openjdk.java.net/jdk8/jdk8/hotspot/file/87ee5ee27509/src/share/vm/prims/unsafe.cpp
inline void* addr_from_java(jlong addr) {
  // This assert fails in a variety of ways on 32-bit systems.
  // It is impossible to predict whether native code that converts
  // pointers to longs will sign-extend or zero-extend the addresses.
  //assert(addr == (uintptr_t)addr, "must not be odd high bits");
  return (void*)(uintptr_t)addr;
}

inline jlong addr_to_java(void* p) {
  //assert(p == (void*)(uintptr_t)p, "must not be odd high bits");
  assert(p == (void*)(uintptr_t)p);
  return (uintptr_t)p;
}

JNIEXPORT void Java_com_intel_pmdevice_initializeNative
  (JNIEnv *env, jclass clazz, jstring path, jlong size) {
  const char* str = env->GetStringUTFChars(path, NULL);
  if (NULL == str) {
    throw std::invalid_argument("pmem initial path can't be NULL.\n");
  }

  //TODO(): create the file 
  fd = ::open(str, O_RDWR);

  size_t map_len;
  addr = (char *)pmem_map_file(str, 0, PMEM_FILE_EXCL, O_RDWR, &map_len, NULL);

  if (NULL == addr) {
    throw std::runtime_error("pmem_map_file failed.\n");
  }
  size = map_len;

  env->ReleaseStringUTFChars(path, str);
}

JNIEXPORT jlong JNICALL Java_com_intel_pmdevice_writeMemory
  (JNIEnv *env, jclass clazz, jlong source, jlong offset, jlong size) {
  if (NULL == addr) {
    throw std::invalid_argument("Initialize should be called before any Intel Optane DC Persistent Memory operation.\n");
  }

  void *buf = addr_from_java(source);
  pmem_memcpy_persist(addr + offset, (const char *)buf, (uint32_t)size);
  return (ssize_t)size;
  //return addr_to_java(p);
}

JNIEXPORT void JNICALL Java_com_intel_pmdevice_freeMemory
  (JNIEnv *env, jclass clazz, jlong address) {
  if (NULL == addr) {
    throw std::invalid_argument("Initialize should be called before any Intel Optane DC Persistent Memory operation.\n");
  }

  pmem_unmap(addr, size);
  ::close(fd);
}

JNIEXPORT void JNICALL Java_com_intel_pmdevice_readMemory
  (JNIEnv *env, jclass clazz, jlong destination, jlong offset, jlong size) {
  size_t sz = (size_t)size;
  void *dest = addr_from_java(destination);
  std::memcpy(dest, addr + offset, sz);
}
