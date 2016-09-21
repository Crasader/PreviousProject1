#import <StoreKit/StoreKit.h>

//代理
@interface RechargeVC : UIViewController <SKPaymentTransactionObserver,SKProductsRequestDelegate >

{
    NSString *buyType;
    NSString *orderId;
}

-(void) buy:(NSString *)type orderId:(NSString *)myOrderId;

-(void) RequestProductData;

-(void) paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions;

-(void) checkReceiptIsValid;

-(void) completeTransaction: (SKPaymentTransaction *)transaction;

-(void) failedTransaction: (SKPaymentTransaction *)transaction;

-(void) restoreTransaction: (SKPaymentTransaction *)transaction;

-(void) paymentQueue:(SKPaymentQueue *) paymentQueue restoreCompletedTransactionsFailedWithError:(NSError *)error;

-(void) paymentQueueRestoreCompletedTransactionsFinished: (SKPaymentTransaction *)transaction;

-(void) provideContent:(NSString *)product;

-(void) recordTransaction:(NSString *)product;

@end