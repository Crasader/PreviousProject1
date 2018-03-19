#import <StoreKit/StoreKit.h>

//代理
@interface RechargeVC : NSObject<SKPaymentTransactionObserver,SKProductsRequestDelegate >


+(instancetype) shareInstance;  

-(void) buy:(NSString*)myOrderId productId:(NSString*) myProductId poxiaoId:(NSString*) myPoxiaoId;

-(void) RequestProductData;

-(void) paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions;

-(void) checkReceiptIsValid:(NSString *) myOrderId receipt:(NSString *)myReceipt;

-(void) completeTransaction: (SKPaymentTransaction *)transaction;

-(void) failedTransaction: (SKPaymentTransaction *)transaction;

-(void) restoreTransaction: (SKPaymentTransaction *)transaction;

-(void) paymentQueue:(SKPaymentQueue *) paymentQueue restoreCompletedTransactionsFailedWithError:(NSError *)error;

-(void) paymentQueueRestoreCompletedTransactionsFinished: (SKPaymentTransaction *)transaction;

-(void) provideContent:(NSString *)product;

-(void) recordTransaction:(NSString *)product;

-(void) openDatabase;

-(void) deleteRecordFromDB:(int) recordId;

-(void) insertRecordToDB;

@end