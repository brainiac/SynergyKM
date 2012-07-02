//
//  SDStatusUpdater.h
//  synergyd
//
//Copyright (c) 2005, Lorenz Schori <lo@znerol.ch>
// All rights reserved.
//
//Redistribution and use in source and binary forms, with or without modification, 
//are permitted provided that the following conditions are met:
//
//	� 	Redistributions of source code must retain the above copyright notice, 
//      this list of conditions and the following disclaimer.
//	� 	Redistributions in binary form must reproduce the above copyright notice,
//      this list of conditions and the following disclaimer in the documentation 
//      and/or other materials provided with the distribution.
//	� 	Neither the name of the Lorenz Schori nor the names of its 
//      contributors may be used to endorse or promote products derived from 
//      this software without specific prior written permission.
//
//THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
//"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
//LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR 
//A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
//OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
//SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
//TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
//OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY 
//OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
//(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE 
//USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#import <Cocoa/Cocoa.h>
#import "SDConstants.h"

#define SDAddStatusUpdateObserverForObject(sel,o) [[NSNotificationCenter defaultCenter] addObserver:self selector:sel name:SDStatusUpdateNotification object:o]
#define SDRemoveStatusUpdateObserverForObject(o) [[NSNotificationCenter defaultCenter] removeObserver:self name:SDStatusUpdateNotification object:o]

#define SDUpdateStatusCode(stat) [[SDStatusUpdater defaultStatusUpdater] postStatusUpdateCode:stat message:nil sender:self]
#define SDUpdateStatusCodeWithMessage(stat,msg) [[SDStatusUpdater defaultStatusUpdater] postStatusUpdateCode:stat message:msg sender:self]
#define SDForwardStatus(notification) [[NSNotificationCenter defaultCenter] postNotificationName:[notification name] object:self userInfo:[notification userInfo]]

@interface SDStatusUpdater : NSObject{
	SDStatusUpdater*		nextReceiver;
	NSMutableDictionary*	statusDict;
	NSMutableDictionary*	imageDict;
	NSMutableDictionary*	aliasDict;
	
	NSDictionary*			lastStatus;
	
	id						statusUpdateSender;
}
+ (id) defaultStatusUpdater;
- (void) setDefaultStatusDictionary:(NSDictionary*)aDictionary statusImageDictionary:(NSDictionary*)anImageDict andAlias:(NSString*)anAlias;
- (void) setStatusDictionary:(NSDictionary*)aDictionary statusImageDictionary:(NSDictionary*)anImageDict andAlias:(NSString*)anAlias forClass:(Class)aClass;

/*
- (void) postLastStatusUpdate;
- (void) setStatusUpdateSender:(id)aSender;
- (id) statusUpdateSender;
*/

- (void) postStatusUpdateCode:(int)aStatus message:(NSString*)aMessage sender:(id)sender;
- (void) postStatusUpdate:(id)aStatus message:(NSString*)aMessage sender:(id)sender;
@end

@interface NSObject (SDStatusUpdaterAddInfo)
- (NSDictionary*)additionalStatusUpdateInfo;
@end

@interface NSObject (SDStatusUpdateSender)
- (void)sendStatusUpdate:(NSDictionary*)status;
@end