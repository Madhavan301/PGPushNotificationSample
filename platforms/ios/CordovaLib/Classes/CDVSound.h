/*
 Licensed to the Apache Software Foundation (ASF) under one
 or more contributor license agreements.  See the NOTICE file
 distributed with this work for additional information
 regarding copyright ownership.  The ASF licenses this file
 to you under the Apache License, Version 2.0 (the
 "License"); you may not use this file except in compliance
 with the License.  You may obtain a copy of the License at
 
 http://www.apache.org/licenses/LICENSE-2.0
 
 Unless required by applicable law or agreed to in writing,
 software distributed under the License is distributed on an
 "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 KIND, either express or implied.  See the License for the
 specific language governing permissions and limitations
 under the License.
 */


#import <Foundation/Foundation.h>
#import <AudioToolbox/AudioServices.h>
#import <AVFoundation/AVFoundation.h>

#import "CDVPlugin.h"




enum CDVMediaError {
	MEDIA_ERR_ABORTED = 1,
	MEDIA_ERR_NETWORK = 2,
	MEDIA_ERR_DECODE = 3,
	MEDIA_ERR_NONE_SUPPORTED = 4
};
typedef NSUInteger CDVMediaError;

enum CDVMediaStates {
	MEDIA_NONE = 0,
	MEDIA_STARTING = 1,
	MEDIA_RUNNING = 2,
	MEDIA_PAUSED = 3,
	MEDIA_STOPPED = 4
};
typedef NSUInteger CDVMediaStates;

enum CDVMediaMsg {
	MEDIA_STATE = 1,
	MEDIA_DURATION = 2,
    MEDIA_POSITION = 3,
	MEDIA_ERROR = 9
};
typedef NSUInteger CDVMediaMsg;

@interface CDVAudioPlayer : AVAudioPlayer
{
	NSString* mediaId;
}
@property (nonatomic,copy) NSString* mediaId;
@end

@interface CDVAudioRecorder : AVAudioRecorder
{
	NSString* mediaId;
}
@property (nonatomic,copy) NSString* mediaId;
@end
	
@interface CDVAudioFile : NSObject
{
	NSString* resourcePath;
	NSURL* resourceURL;
	CDVAudioPlayer* player;
	CDVAudioRecorder* recorder;
    NSNumber* volume;
}

@property (nonatomic, strong) NSString* resourcePath;
@property (nonatomic, strong) NSURL* resourceURL;
@property (nonatomic, strong) CDVAudioPlayer* player;
@property (nonatomic, strong) NSNumber* volume;

@property (nonatomic, strong) CDVAudioRecorder* recorder;

@end

@interface CDVSound : CDVPlugin <AVAudioPlayerDelegate, AVAudioRecorderDelegate>
{
	NSMutableDictionary* soundCache;
    AVAudioSession* avSession;
}
@property (nonatomic, strong) NSMutableDictionary* soundCache;
@property (nonatomic, strong) AVAudioSession* avSession;
//DEPRECATED
- (void) play:(CDVInvokedUrlCommand*)command __attribute__((deprecated));	  	
- (void) pause:(CDVInvokedUrlCommand*)command __attribute__((deprecated));
- (void) stop:(CDVInvokedUrlCommand*)command __attribute__((deprecated));
// DEPRECATED

- (void) startPlayingAudio:(CDVInvokedUrlCommand*)command;
- (void) pausePlayingAudio:(CDVInvokedUrlCommand*)command;
- (void) stopPlayingAudio:(CDVInvokedUrlCommand*)command;
- (void) seekToAudio:(CDVInvokedUrlCommand*)command;
- (void) release:(CDVInvokedUrlCommand*)command;
- (void) getCurrentPositionAudio:(CDVInvokedUrlCommand*)command;

// DEPRECATED
- (void) getCurrentPosition:(CDVInvokedUrlCommand*)command __attribute__((deprecated));
- (void) prepare:(CDVInvokedUrlCommand*)command __attribute__((deprecated));
// DEPRECATED

- (BOOL) hasAudioSession;

// helper methods
- (CDVAudioFile*) audioFileForResource:(NSString*) resourcePath withId: (NSString*)mediaId;
- (BOOL) prepareToPlay: (CDVAudioFile*) audioFile withId: (NSString*)mediaId;
- (NSString*) createMediaErrorWithCode: (CDVMediaError) code message: (NSString*) message;

// DEPRECATED
- (void) startAudioRecord:(CDVInvokedUrlCommand*)command __attribute__((deprecated));
- (void) stopAudioRecord:(CDVInvokedUrlCommand*)command __attribute__((deprecated));
// DEPRECATED

- (void) startRecordingAudio:(CDVInvokedUrlCommand*)command;
- (void) stopRecordingAudio:(CDVInvokedUrlCommand*)command;

- (void) setVolume:(CDVInvokedUrlCommand*)command;

@end
