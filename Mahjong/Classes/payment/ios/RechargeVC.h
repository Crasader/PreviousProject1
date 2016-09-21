#import <StoreKit/StoreKit.h>

//代理
@interface RechargeVC : UIViewController <SKPaymentTransactionObserver,SKProductsRequestDelegate >

{
    NSString *buyType;
    NSString *orderId;
}

-(void) requestProUpgradeProductData;

-(void) RequestProductData;

-(void) buy:(NSString *)type orderId:(NSString *)myOrderId;

-(void) paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions;

-(void) PurchasedTransaction: (SKPaymentTransaction *)transaction;

-(void) completeTransaction: (SKPaymentTransaction *)transaction;

-(void) checkReceiptIsValid;

-(void) failedTransaction: (SKPaymentTransaction *)transaction;

-(void) paymentQueueRestoreCompletedTransactionsFinished: (SKPaymentTransaction *)transaction;

-(void) paymentQueue:(SKPaymentQueue *) paymentQueue restoreCompletedTransactionsFailedWithError:(NSError *)error;

-(void) restoreTransaction: (SKPaymentTransaction *)transaction;

-(void) provideContent:(NSString *)product;

-(void) recordTransaction:(NSString *)product;

@end