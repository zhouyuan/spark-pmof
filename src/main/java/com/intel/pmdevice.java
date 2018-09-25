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

package com.intel;


import sun.misc.Cleaner;

import java.lang.reflect.Constructor;
import java.lang.reflect.Field;
import java.nio.ByteBuffer;

public class pmdevice {
  private static final Object lock = new Object();
  private static boolean initialized = false;

  static {
    NativeLoader.loadLibrary("pmdevice");
  }


  public static void initialize(String initializePath, long initializeSize) {
    if (!initialized) {
      synchronized (lock) {
        if (!initialized) {
          initializeNative(initializePath, initializeSize);
          initialized = true;
        }
      }
    }
  }

  private static native void initializeNative(String initializePath, long initializeSize);

  public static native long writeMemory(long address, long offset, long size);

  public static ByteBuffer allocateDirectBuffer(int size) {
    try {
      Class<?> cls = Class.forName("java.nio.DirectByteBuffer");
      Constructor<?> constructor = cls.getDeclaredConstructor(Long.TYPE, Integer.TYPE);
      constructor.setAccessible(true);
      Field cleanerField = cls.getDeclaredField("cleaner");
      cleanerField.setAccessible(true);
      //FIXME
      final long memory = writeMemory(size, size, size);
      ByteBuffer buffer = (ByteBuffer) constructor.newInstance(memory, size);
      Cleaner cleaner = Cleaner.create(buffer, new Runnable() {
        @Override
        public void run() {
          freeMemory(memory);
        }
      });
      cleanerField.set(buffer, cleaner);
      return buffer;
    } catch (Exception e) {
      throw new RuntimeException(e);
    }
  }

  public static native void freeMemory(long address);

  public static native void readMemory(long destAddress, long srcAddress, long size);
}
