#import "wechat/ios/RechargeVC.h"
#import "wechat/ios/WxLoginHandler.h"
#include "mahjong/GameConfig.h"
#import "sqlite3.h"

@implementation RechargeVC

static RechargeVC* _instance = nil;

bool hasAddObersver = NO;

NSString *iosProductId = nil;

NSString *poxiaoOrderId = nil;

NSString *poxiaoId = nil;

sqlite3 *poxiaoDB = nil;


+(instancetype) shareInstance
{
    @synchronized(self)
    {
        static dispatch_once_t onceToken ;
        dispatch_once(&onceToken, ^{
            _instance = [[super allocWithZone:NULL] init] ;
            
        }) ;
    }
    return _instance ;
}

+(id) allocWithZone:(struct _NSZone *)zone
{
    return [RechargeVC shareInstance] ;
}

-(id) copyWithZone:(struct _NSZone *)zone
{
    return [RechargeVC shareInstance] ;
}

-(void) buy:(NSString*)myOrderId productId:(NSString*) myProductId poxiaoId:(NSString*) myPoxiaoId
{
    if ([SKPaymentQueue canMakePayments]) {
        NSLog(@"允许程序内付费购买");
        iosProductId = myProductId;
        poxiaoOrderId = myOrderId;
        poxiaoId = myPoxiaoId;
        
        //注册监听事件
        if (!hasAddObersver) {
            hasAddObersver = YES;
            // 监听购买结果
            [[SKPaymentQueue defaultQueue] addTransactionObserver:self];
            [self openDatabase];
        }
        //向IOS服务器发送请求,获取商品信息
        [self RequestProductData];
                NSLog(@"---发送购买请求---%@",iosProductId);
//                SKPayment *payment = [SKPayment paymentWithProductIdentifier:iosProductId];
//                [[SKPaymentQueue defaultQueue] addPayment:payment];
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
    NSArray *product =[[NSArray alloc] initWithObjects:iosProductId,nil];
    NSSet *nsset = [NSSet setWithArray:product];
    SKProductsRequest *request=[[SKProductsRequest alloc] initWithProductIdentifiers: nsset];
    request.delegate=self;
    [request start];
}

-(void) productsRequest:(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response{
    
    NSLog(@"---收到产品反馈信息---");
    NSArray *myProduct = response.products;
    NSLog(@"产品Product ID:%@",response.invalidProductIdentifiers);
    if (myProduct.count == 0) {
        NSLog(@"无法获取产品信息，购买失败。");
        UIAlertView *alerView =  [[UIAlertView alloc] initWithTitle:@"提示" message:@"无法获取产品信息，购买失败。" delegate:nil cancelButtonTitle:NSLocalizedString(@"关闭",nil) otherButtonTitles:nil];
        [alerView show];
        return;
    }
    for(SKProduct *product in myProduct){
        NSLog(@"product info");
        NSLog(@"SKProduct 描述信息%@", [product description]);
        NSLog(@"产品标题 %@" , product.localizedTitle);
        NSLog(@"产品描述信息: %@" , product.localizedDescription);
        NSLog(@"价格: %@" , product.price);
        NSLog(@"Product id: %@" , product.productIdentifier);
    }
    NSLog(@"---发送购买请求---");
    SKPayment * payment = [SKPayment paymentWithProductIdentifier:iosProductId];
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


-(void) checkReceiptIsValid:(NSString *) myOrderId receipt:(NSString *)myReceipt{
    NSLog(@"---checkReceiptIsValid---");
    //第一步，创建URL
    NSString *urlstring = [NSString stringWithFormat:@"%s",APP_STORE_PAY_ORDER];
    NSURL *url = [NSURL URLWithString:urlstring];
    //第二步，创建请求
    NSMutableURLRequest *request = [[NSMutableURLRequest alloc]initWithURL:url cachePolicy:NSURLRequestUseProtocolCachePolicy timeoutInterval:10];
    //    NSString *post = [NSString stringWithFormat:@"{order_id:%@,receipt:%@}",myOrderId,myReceipt];
    //    NSData *postData = [post dataUsingEncoding:NSUTF8StringEncoding allowLossyConversion:YES];
    NSDictionary *tmp = [[NSDictionary alloc] initWithObjectsAndKeys:myOrderId, @"order_id",myReceipt, @"receipt",nil];
    NSError *error;
    NSData *postData = [NSJSONSerialization dataWithJSONObject:tmp options:0 error:&error];
    [request setHTTPMethod:@"POST"];//设置请求方式为POST，默认为GET
    [request setValue:@"text/html" forHTTPHeaderField:@"Content-Type"];
    [request setHTTPBody:postData];
    //第三步，连接服务器
    NSData *received = [NSURLConnection sendSynchronousRequest:request returningResponse:nil error:nil];
    NSString *result = [[NSString alloc]initWithData:received encoding:NSUTF8StringEncoding];
    //    NSLog(@"received = %@",result);
    //刷新用户信息
    WxLoginHandler::getInstance()->updatePlayerInfo("IAP");
    [self deleteRecordFromDB:[poxiaoOrderId intValue]];
}


-(void) completeTransaction: (SKPaymentTransaction *)transaction{
    NSLog(@"---completeTransaction---");
    //交易完成,向服务器进行验证
    [[SKPaymentQueue defaultQueue] finishTransaction: transaction];
    NSData *data = [NSData dataWithContentsOfFile:[[[NSBundle mainBundle] appStoreReceiptURL] path]];
    NSString *myReceipt = [data base64EncodedStringWithOptions:0];
    [self insertRecordToDB]; //存到本地
    [self checkReceiptIsValid:poxiaoOrderId receipt:myReceipt];//receipt发送到服务器验证是否有效
    
}


-(void) failedTransaction: (SKPaymentTransaction *)transaction{
    NSLog(@"---failedTransaction---");
    NSLog(@"error:%@",transaction.error);
//    NSString *rssiString = [NSString stringWithFormat:@"%d", transaction.error.code];
//    NSLog(@"errorcode = %@",rssiString);
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
    UIAlertView *alerView2 = [[UIAlertView alloc] initWithTitle:@"提示" message:@"已经购买过该商品了" delegate:nil cancelButtonTitle:NSLocalizedString(@"关闭",nil) otherButtonTitles:nil];
    [alerView2 show];
    [[SKPaymentQueue defaultQueue] finishTransaction: transaction];
}

-(void) recordTransaction:(NSString *)product{
    NSLog(@"-----记录交易--------");
}


-(void) provideContent:(NSString *)product{
    NSLog(@"-----下载--------");
}

/**
 *  打开数据库并创建一个表
 */
- (void)openDatabase {
    //1.设置文件名
    NSString *filename = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES).firstObject stringByAppendingPathComponent:@"poxiao_user_info.db"];
    //2.打开数据库文件，如果没有会自动创建一个文件
    NSInteger result = sqlite3_open(filename.UTF8String, &poxiaoDB);
    if (result == SQLITE_OK) {
        NSLog(@"打开数据库成功！");
        //3.创建一个数据库表
        char *errmsg = NULL;
        sqlite3_exec(poxiaoDB, "CREATE TABLE IF NOT EXISTS t_person(id integer primary key autoincrement, poxiaoId text, productId text, orderId text)", NULL, NULL, &errmsg);
        if (errmsg) {
            NSLog(@"错误：%s", errmsg);
        } else {
            NSLog(@"创表成功！");
        }
        
    } else {
        NSLog(@"打开数据库失败！");
    }}

-(void) insertRecordToDB{
    NSLog(@"插入一条数据！");
    NSString *inSQL = [NSString stringWithFormat:@"INSERT INTO 't_person' ('%@', '%@', '%@') VALUES ('%@', '%@', '%@')",
                       @"poxiaoId", @"productId", @"orderId", poxiaoId, iosProductId, poxiaoOrderId];
    char *errmsg = NULL;
    const char * sql =[inSQL UTF8String];
    sqlite3_exec(poxiaoDB, sql, NULL, NULL, &errmsg);
}

-(void) deleteRecordFromDB:(int) recordId{
    NSLog(@"删除一条数据！%d",recordId);
    NSString *deleteSqlStr = [NSString stringWithFormat:@"DELETE FROM 't_person' WHERE  orderId= %@",poxiaoOrderId];
    char *errmsg = NULL;
    const char * sql =[deleteSqlStr UTF8String];
    sqlite3_exec(poxiaoDB, sql, NULL, NULL, &errmsg);
}



-(void) dealloc
{
    [super dealloc];
    [[SKPaymentQueue defaultQueue] removeTransactionObserver:self];//解除监听
    sqlite3_close(poxiaoDB);
}

@end
