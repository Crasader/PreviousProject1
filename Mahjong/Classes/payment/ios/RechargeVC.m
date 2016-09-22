#import "payment/ios/RechargeVC.h"

@interface RechargeVC ()

@end

@implementation RechargeVC

static bool hasAddObersver = NO;

- (id)init {
    //指定的初始化函数
    if (!hasAddObersver) {
        hasAddObersver = YES;
        // 监听购买结果
        [[SKPaymentQueue defaultQueue] addTransactionObserver:self];
    }
    return (self);
}

-(void) buy:(NSString*)type orderId:(NSString *)myOrderId
{
    
    buyType = type;
    orderId = myOrderId;
    if ([SKPaymentQueue canMakePayments]) {
        NSLog(@"允许程序内付费购买");
        //      [self RequestProductData];//向IOS服务器发送请求,获取商品信息
        NSLog(@"---发送购买请求---");
        SKPayment *payment = [SKPayment paymentWithProductIdentifier:buyType];
        [[SKPaymentQueue defaultQueue] addPayment:payment];
    }
    else
    {
        NSLog(@"不允许程序内付费购买");
        UIAlertView *alerView =  [[UIAlertView alloc] initWithTitle:@"提示" message:@"您的手机没有打开程序内付费购买" delegate:nil cancelButtonTitle:NSLocalizedString(@"关闭",nil) otherButtonTitles:nil];
        [alerView show];
    }
}

-(void) RequestProductData
{
    NSLog(@"---请求对应的产品信息---");
    NSArray *product =[[NSArray alloc] initWithObjects:buyType,nil];
    NSSet *nsset = [NSSet setWithArray:product];
    SKProductsRequest *request=[[SKProductsRequest alloc] initWithProductIdentifiers: nsset];
    request.delegate=self;
    [request start];
}

-(void) productsRequest:(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response{
    
    NSLog(@"---收到产品反馈信息---");
    NSArray *myProduct = response.products;
    NSLog(@"产品Product ID:%@",response.invalidProductIdentifiers);
    NSLog(@"产品付费数量: %d", (int)[myProduct count]);
    for(SKProduct *product in myProduct){
        NSLog(@"product info");
        NSLog(@"SKProduct 描述信息%@", [product description]);
        NSLog(@"产品标题 %@" , product.localizedTitle);
        NSLog(@"产品描述信息: %@" , product.localizedDescription);
        NSLog(@"价格: %@" , product.price);
        NSLog(@"Product id: %@" , product.productIdentifier);
    }
    NSLog(@"---发送购买请求---");
    SKPayment * payment = [SKPayment paymentWithProductIdentifier:buyType];
    [[SKPaymentQueue defaultQueue] addPayment:payment];
}


-(void) requestDidFinish:(SKRequest *)request
{
    NSLog(@"---商品信息请求结束----");
    
}

-(void) request:(SKRequest *)request didFailWithError:(NSError *)error {
    NSLog(@"商品信息请求错误:%@", error);
}

-(void) paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions//交易结果
{
    NSLog(@"---updatedTransactions---");
    for (SKPaymentTransaction *transaction in transactions)
    {
        switch (transaction.transactionState)
        {
            case SKPaymentTransactionStatePurchased:
                NSLog(@"-----交易完成 --------");
                [self completeTransaction:transaction];
                break;
            case SKPaymentTransactionStateFailed://交易失败
                NSLog(@"-----交易失败 --------");
                [self failedTransaction:transaction];
                break;
            case SKPaymentTransactionStateRestored://已经购买过该商品
                NSLog(@"-----已经购买过该商品 --------");
                [self restoreTransaction:transaction];
                break;
            case SKPaymentTransactionStatePurchasing:      //商品添加进列表
                NSLog(@"-----商品添加进列表 --------");
                break;
            default:
                break;
        }
    }
}


-(void) paymentQueueRestoreCompletedTransactionsFinished: (SKPaymentTransaction *)transaction{
    NSLog(@"----paymentQueueRestoreCompletedTransactionsFinished----");
}

-(void) paymentQueue:(SKPaymentQueue *) paymentQueue restoreCompletedTransactionsFailedWithError:(NSError *)error{
    NSLog(@"----restoreCompletedTransactionsFailedWithError----");
}


-(void) checkReceiptIsValid{
    NSLog(@"---checkReceiptIsValid---");
    //创建URL对象
    NSString *urlStr = @"http://183.129.206.54:1111/pay!iosOrderVerify.action?order_id=11111&receipt=weqewqewqeqew";
    NSURL *url = [[NSURL alloc] initWithString:urlStr];
    NSURLRequest *request = [[NSURLRequest alloc]initWithURL:url cachePolicy:NSURLRequestUseProtocolCachePolicy timeoutInterval:10];
    /*其中缓存协议是个枚举类型包含：
     NSURLRequestUseProtocolCachePolicy（基础策略）
     NSURLRequestReloadIgnoringLocalCacheData（忽略本地缓存）
     NSURLRequestReturnCacheDataElseLoad（首先使用缓存，如果没有本地缓存，才从原地址下载）
     NSURLRequestReturnCacheDataDontLoad（使用本地缓存，从不下载，如果本地没有缓存，则请求失败，此策略多用于离线操作）
     NSURLRequestReloadIgnoringLocalAndRemoteCacheData（无视任何缓存策略，无论是本地的还是远程的，总是从原地址重新下载）
     NSURLRequestReloadRevalidatingCacheData（如果本地缓存是有效的则不下载，其他任何情况都从原地址重新下载）*/
    //第三步，连接服务器
    NSData *received = [NSURLConnection sendSynchronousRequest:request returningResponse:nil error:nil];
    NSString *str = [[NSString alloc]initWithData:received encoding:NSUTF8StringEncoding];
    NSLog(@"%@",str);
}


-(void) completeTransaction: (SKPaymentTransaction *)transaction{
    NSLog(@"---completeTransaction---");
    //交易完成,向服务器进行验证
    //self.receipt = [GTMBase64 stringByEncodingData:[NSData dataWithContentsOfURL:[[NSBundle mainBundle] appStoreReceiptURL]]];
    [self checkReceiptIsValid];//把self.receipt发送到服务器验证是否有效
    // Your application should implement these two methods.
    //    NSString *product = transaction.payment.productIdentifier;
    //    if ([product length] > 0) {
    //
    //        NSArray *tt = [product componentsSeparatedByString:@"."];
    //        NSString *bookid = [tt lastObject];
    //        if ([bookid length] > 0) {
    //            [self recordTransaction:bookid];
    //            [self provideContent:bookid];
    //        }
    //    }
    // Remove the transaction from the payment queue.
    [[SKPaymentQueue defaultQueue] finishTransaction: transaction];
}


-(void) failedTransaction: (SKPaymentTransaction *)transaction{
    NSLog(@"---failedTransaction---");
    if (transaction.error.code != SKErrorPaymentCancelled)
    {
        
    }
    UIAlertView *alerView2 = [[UIAlertView alloc] initWithTitle:@"提示" message:@"购买失败，请重新尝试购买" delegate:nil cancelButtonTitle:NSLocalizedString(@"关闭",nil) otherButtonTitles:nil];
    [alerView2 show];
    [[SKPaymentQueue defaultQueue] finishTransaction: transaction];
}


-(void) restoreTransaction: (SKPaymentTransaction *)transaction
{
    NSLog(@"---交易恢复处理---");
    [[SKPaymentQueue defaultQueue] finishTransaction: transaction];
}

-(void) recordTransaction:(NSString *)product{
    NSLog(@"-----记录交易--------");
}


-(void) provideContent:(NSString *)product{
    NSLog(@"-----下载--------");
}

-(void) dealloc
{
    [super dealloc];
    [[SKPaymentQueue defaultQueue] removeTransactionObserver:self];//解除监听
}

@end