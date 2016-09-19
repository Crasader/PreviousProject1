#import <StoreKit/StoreKit.h>

//代理
@interface RechargeVC : UIViewController <SKPaymentTransactionObserver,SKProductsRequestDelegate >

{
    int buyType;
}

-(void) requestProUpgradeProductData;

-(void) RequestProductData;

-(void) buy:(int)type;

-(void) paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions;

-(void) PurchasedTransaction: (SKPaymentTransaction *)transaction;

-(void) completeTransaction: (SKPaymentTransaction *)transaction;

-(void) failedTransaction: (SKPaymentTransaction *)transaction;

-(void) paymentQueueRestoreCompletedTransactionsFinished: (SKPaymentTransaction *)transaction;

-(void) paymentQueue:(SKPaymentQueue *) paymentQueue restoreCompletedTransactionsFailedWithError:(NSError *)error;

-(void) restoreTransaction: (SKPaymentTransaction *)transaction;

-(void) provideContent:(NSString *)product;

-(void) recordTransaction:(NSString *)product;

@end