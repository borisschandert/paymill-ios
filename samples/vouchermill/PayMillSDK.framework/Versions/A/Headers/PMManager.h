//
//  PMManager.h
//  PayMillSDK
//
//  Created by PayMill on 2/22/13.
//  Copyright (c) 2013 PayMill. All rights reserved.
//
#import "PMManager.h"
#import "PMPaymentMethod.h"
#import "PMPaymentParams.h"
#import "PMError.h"
#import "PMTransaction.h"
#import "PMPreauthorization.h"

//Block callbacks
/*Get non consumed transactions*/
typedef void (^OnNotConsumedTransactionsSuccess)(NSArray *notConsumedTransactions);
typedef void (^OnNotConsumedTransactionsFailure)(NSError *error);
/*Get non consumed preauthorizations*/
typedef void (^OnNotConsumedPreauthorizationsSuccess)(NSArray *notConsumedPreauthorizations);
typedef void (^OnNotConsumedPreauthorizationsFailure)(NSError *error);
/*Create token*/
typedef void (^OnTokenSuccess)(NSString* token);
typedef void (^OnTokenFailure)(NSError *error);
/*Create Transaction*/
typedef void (^OnTransactionSuccess)(PMTransaction* transaction);
typedef void (^OnTransactionFailure)(NSError *error);
/*Create Preauthorization*/
typedef void (^OnPreauthorizationSuccess)(PMTransaction* transaction);
typedef void (^OnPreauthorizationFailure)(NSError *error);
/*Get Transactions*/
typedef void (^OnTransactionsListSuccess)(NSArray* transactions);
typedef void (^OnTransactionsListFailure)(NSError *error);
/*Get Prauthorizations*/
typedef void (^OnPreauthorizationsListSuccess)(NSArray* preauthorizations);
typedef void (^OnPreauthorizationsListFailure)(NSError *error);
/*Get new Device Id*/
typedef void(^OnDeviceIdSucces)(NSString *devicId);
typedef void(^OnDeviceIdFailure)(NSError *error);
/*Init*/
typedef void(^OnInit)(BOOL success, NSError *error);
/*Consume transaction/preauthorization*/
typedef void(^OnConsumeSuccess)(NSString * id);
typedef void(^OnConsumeFailure)(NSError *error);
/**
 This class is the main entry point for all SDK calls.
 */
@interface PMManager : NSObject
/**
 Initializes the SDK. This should always be the first call you make, when you use the SDK.
 @param testMode true for TEST mode, false for LIVE mode.
 @param merchantPublicKey your PayMill public key for LIVE or TEST mode, depending on the previous parameter.
 @param newDeviceId an optional deviceID.
 Note: You cannot specify an arbitrary string. The device ID must have been generated by the SDK, for example with getNewDeviceId() . You can use this parameter to associate end users in your applications with SDK deviceIDs.If you don't specify a device ID, the SDK will generate one and save it for later use.
 @param init block function of type OnInit that will be called on success or failure
 */
+(void) initWithTestMode:(BOOL)testmode merchantPublicKey:(NSString*)merchantPublicKey newDeviceId:(NSString*)newDeviceId
					init:(OnInit)onInit;
/**
 Initializes the SDK. This should always be the first call you make, when you use the SDK.
 @param testMode true for TEST mode, false for LIVE mode.
 @param merchantPublicKey your PayMill public key for LIVE or TEST mode, depending on the previous parameter.
 @param newDeviceId an optional deviceID.
 Note: You cannot specify an arbitrary string. The device ID must have been generated by the SDK, for example with getNewDeviceId() . You can use this parameter to associate end users in your applications with SDK deviceIDs.If you don't specify a device ID, the SDK will generate one and save it for later use.
 @param init block callback that will be called on success or failure
 @param successTranBlock optional block callback for getting all not consumed PMTrаnsaction objects. The block will be called on success.
 @param failureTranBlock optional block callback that will be called on failure when getting all not consumed PMTrаnsaction objects.
 @param successPreauthBlock optional block callback for getting all not consumed PMPreauthorization objects. The block will be called on success.
 @param failurePreauthBlock optional block callback that will be called on failure when getting all not consumed PMPreauthorization objects.
*/
+(void) initWithTestMode:(BOOL)testmode merchantPublicKey:(NSString*)merchantPublicKey newDeviceId:(NSString*)newDeviceId
					init:(OnInit)onInit success:(OnNotConsumedTransactionsSuccess)successTranBlock
				 failure:(OnNotConsumedTransactionsFailure)failureTranBlock
				 success:(OnNotConsumedPreauthorizationsSuccess)successPreauthBlock
				 failure:(OnNotConsumedPreauthorizationsFailure)failurePreauthBlock;

/**
 Creates a new PMPreauthorization.
 This is a convenience method, which generates a token in the background.
 @param method PMPaymentMethod created with PMFactory.
 @param parameters PMPaymentParams created with PMFactory.
 @param consumable true if you want to consume the preauthorization later, false otherwise.
 @param success a block callback that is executed when the preauthorization is created successfully.
 @param failure a block callback that is executed when the preauthorization creation failed.
 */
+(void) preauthorizationWithMethod:(id<PMPaymentMethod>)method parameters:(PMPaymentParams*)params consumable:(BOOL)consumable
						   success:(OnPreauthorizationSuccess)successBlock
						   failure:(OnPreauthorizationFailure)failureBlock;

/**
 Creates a new PMTransaction.
 This is a convenience method, which generates a token in the background.
 @param method PMPaymentMethod created with PMFactory.
 @param parameters PMPaymentParams created with PMFactory.
 @param consumable true if you want to consume the preauthorization later, false otherwise.
 @param success a block callback that is executed when the transaction is created successfully.
 @param failure a block callback that is executed when the transaction creation failed.
 */
+(void) transactionWithMethod:(id<PMPaymentMethod>)method parameters:(PMPaymentParams*)params consumable:(BOOL)consumable
					  success:(OnTransactionSuccess)successBlock
					  failure:(OnTransactionFailure)failureBlock;

/**
 Creates a new PMPreauthorization.
 @param token a previously generated token.
 @param parameters PMPaymentParams created with PMFactory.
 @param consumable true if you want to consume the preauthorization later, false otherwise.
 @param success a block callback that is executed when the preauthorization is created successfully.
 @param failure a block callback that is executed when the preauthorization creation failed.
 */
+(void) preauthorizationWithToken:(NSString*)token parameters:(PMPaymentParams*)params consumable:(BOOL)consumable
						  success:(OnPreauthorizationSuccess)successBlock
						  failure:(OnPreauthorizationFailure)failureBlock;

/**
 Creates a new PMTransaction.
 @param token a previously generated token.
 @param parameters PMPaymentParams created with PMFactory.
 @param consumable true if you want to consume the preauthorization later, false otherwise.
 @param success a block callback that is executed when the transaction is created successfully.
 @param failure a block callback that is executed when the transaction creation failed.
 */
+(void) transactionWithToken:(NSString*)token parameters:(PMPaymentParams*)params consumable:(BOOL)consumable
					 success:(OnTransactionSuccess)successBlock
					 failure:(OnTransactionFailure)failureBlock;
/**
 Creates a new token.
 Learn more about tokens in the PayMill documentation(https://www.paymill.com/en-gb/documentation-3/).
 @param method PMPaymentMethod created with PMFactory.
 @param parameters PMPaymentParams created with PMFactory. It may be nil
 @param success a block callback that is executed when the token is created successfully.
 @param failure a block callback that is executed when the token creation failed.
 */
+(void) generateTokenWithMethod:(id<PMPaymentMethod>)method parameters:(PMPaymentParams*)params
						success:(OnTokenSuccess)successBlock
						failure:(OnTokenFailure)failureBlock;
/**
 Creates a new token.
 Learn more about tokens in the PayMill documentation(https://www.paymill.com/en-gb/documentation-3/).
 @param method PMPaymentMethod created with PMFactory.
 @param success a block callback that is executed when the token is created successfully.
 @param failure a block callback that is executed when the token creation failed.
 */

+(void) generateTokenWithMethod:(id<PMPaymentMethod>)method
						success:(OnTokenSuccess)successBlock
						failure:(OnTokenFailure)failureBlock;
/**
 This is the preferred way to use the SDK.
 Generate a token using this method and use it in your backend to process transactions, preauthorizations or any other future available trough the PayMill API.
 Learn more about tokens in the PayMill documentation(https://www.paymill.com/en-gb/documentation-3/).
 @param merchantPublicKey your PayMill public key for LIVE or TEST mode, depending on the previous parameter.
 @param testMode true for TEST mode, false for LIVE mode.
 @param method PMPaymentMethod created with PMFactory. It may be nil.
 @param parameters PMPaymentParams created with PMFactory.
 @param success a block callback that is executed when the token is created successfully.
 @param failure a block callback that is executed when the token creation failed.
 */


+(void) generateTokenWithPublicKey:(NSString*)merchantPublicKey testMode:(BOOL) testMode method:(id<PMPaymentMethod>)method parameters:(PMPaymentParams*)params
						success:(OnTokenSuccess)successBlock
						failure:(OnTokenFailure)failureBlock;


/**
 This is the preferred way to use the SDK.
 Generate a token using this method and use it in your backend to process transactions, preauthorizations or any other future available trough the PayMill API.
 Learn more about tokens in the PayMill documentation(https://www.paymill.com/en-gb/documentation-3/).
 @param merchantPublicKey your PayMill public key for LIVE or TEST mode, depending on the previous parameter.
 @param testMode true for TEST mode, false for LIVE mode.
 @param method PMPaymentMethod created with PMFactory. It may be nil.
 @param parameters PMPaymentParams created with PMFactory.
 @param success a block callback that is executed when the token is created successfully.
 @param failure a block callback that is executed when the token creation failed.
 */


+(void) generateTokenWithPublicKey:(NSString*)merchantPublicKey testMode:(BOOL) testMode method:(id<PMPaymentMethod>)method
					success:(OnTokenSuccess)successBlock
					failure:(OnTokenFailure)failureBlock;
/**
 Lists all transactions for the configured deviceId.
 @param success a block callback that is executed when the transactions were listed successfully.
 @param failure a block callback that is executed when the listing the transactions failed.
 */

+(void) getTransactionsList:
(OnTransactionsListSuccess)successBlock
					failure:(OnTransactionFailure)failureBlock;

/**
 Get a specific PMTransaction.
 @param transactionId the id of the transaction.
 @param success a block callback that is executed when the transaction is get successfully.
 @param failure a block callback that is executed when the transaction getting failed.
 */
+(void) getTransactionForId:(NSString*)transactionId
					success:(OnTransactionSuccess)successBlock
					failure:(OnTransactionFailure)failureBlock;

/**
 Lists all preauthorizations for the configured deviceId.
 @param success a block callback that is executed when the preauthorizations were listed succesсfully.
 @param failure a block callback that is executed when the listing the preauthorizations failed.
 */
+(void) getPreauthorizationsList:
(OnPreauthorizationsListSuccess)successBlock
					   onFailure:(OnPreauthorizationsListFailure)failureBlock;

/**
 Get a specific PMPreauthorization.
 @param transactionId the id of the transaction.
 @param success a block callback that is executed when the preauthorization is get successfully.
 @param failure a block callback that is executed when the preauthorization getting failed.
 */
+(void) getPreauthorzationForId:(NSString*)preauthorizationId
						success:(OnPreauthorizationSuccess)successBlock
						failure:(OnPreauthorizationFailure)failureBlock;

/**
 Lists all not consumed PMTransaction objects for the configured deviceId.
 @param success a block callback that is executed when the transactions were listed successfully.
 @param failure a block callback that is executed when the listing the transactions failed.
 */
+(void) getNonConsumedTransactionsList:
(OnNotConsumedTransactionsSuccess)successBlock
							   failure:(OnNotConsumedTransactionsFailure)failureBlock;

/**
 Lists all not consumed PMPreauthorization objects for the configured deviceId.
 @param success a block callback that is executed when the preauthorizations were listed successfully.
 @param failure a block callback that is executed when the listing the preauthorizations failed.
 */
+(void) getNonConsumedPreauthorizationsList:(OnNotConsumedPreauthorizationsSuccess)successBlock
									failure:(OnNotConsumedPreauthorizationsFailure)failureBlock;

/**
 Consume the given transaction. After successful consumption, the transaction will no longer appear in the list of not consumed.
 @param transactionId the id of the transaction.
 @param success a block callback that is executed when the transaction is consumed successfully.
 @param failure a block callback that is executed when the transaction consumption failed.
 */
+(void) consumeTransactionForId:(NSString*)transactionId
						success:(OnConsumeSuccess)successBlock
						failure:(OnConsumeFailure)failureBlock;

/**
 Consume the given preauthorization. After successful consumption, the preauthorization will no longer appear in the list of not consumed.
 @param preauthorizationId the id of the preauthorization.
 @param success a block callback that is executed when the preauthorization is consumed successfully.
 @param failure a block callback that is executed when the preauthorization consumption failed.
 */
+(void) consumePreauthorizationForId:(NSString*)preauthorizationId
							 success:(OnConsumeSuccess)successBlock
							 failure:(OnConsumeFailure)failureBlock;

/**
 Creates new device id.
 @param success a block callback that is executed when the new device id is created successfully.
 @param failure a block callback that is executed when the device id creation failed.
 */
+(void)getNewDeviceIdWithBlock:(OnDeviceIdSucces)successBlock
					 failure:(OnDeviceIdFailure)failureBlock;

/**
 Returns the current device id.
 @return the id or null if none is set.
 */
+(NSString*)getDeviceId;
/**
 Returns YES, if the SDK was initialized, NO otherwise.
 */
+(BOOL)isInit;
/**
 Returns the current SDK version as string.
 @return the SDK version.
 */
+(NSString*)SDKVersion;
@end