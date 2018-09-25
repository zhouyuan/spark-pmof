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

/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_intel_pmdevice */

#ifndef _Included_com_intel_pmdevice
#define _Included_com_intel_pmdevice
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_intel_pmdevice
 * Method:    initializeNative
 * Signature: (Ljava/lang/String;J)V
 */
JNIEXPORT void JNICALL Java_com_intel_pmdevice_initializeNative
  (JNIEnv *, jclass, jstring, jlong);

/*
 * Class:     com_intel_pmdevice
 * Method:    allocateMemory
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_com_intel_pmdevice_writeMemory
  (JNIEnv *, jclass, jlong, jlong, jlong);

/*
 * Class:     com_intel_pmdevice
 * Method:    freeMemory
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_intel_pmdevice_freeMemory
  (JNIEnv *, jclass, jlong);

/*
 * Class:     com_intel_pmdevice
 * Method:    copyMemory
 * Signature: (JJJ)V
 */
JNIEXPORT void JNICALL Java_com_intel_pmdevice_readMemory
  (JNIEnv *, jclass, jlong, jlong, jlong);

#ifdef __cplusplus
}
#endif
#endif