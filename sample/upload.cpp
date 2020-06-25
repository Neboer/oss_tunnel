#include <alibabacloud/oss/OssClient.h>
using namespace AlibabaCloud::OSS;

void upload_file_to(OssClient client, std::string BucketName, std::string ObjectName){
    /* 上传文件 */
    /* yourLocalFilename由本地文件路径加文件名包括后缀组成，例如/users/local/myfile.txt */
    auto outcome = client.PutObject(BucketName, ObjectName,"/home/neboer/program/zhongwei.c");

    if (!outcome.isSuccess()) {
        /* 异常处理 */
        std::cout << "PutObject fail" <<
                  ",code:" << outcome.error().Code() <<
                  ",message:" << outcome.error().Message() <<
                  ",requestId:" << outcome.error().RequestId() << std::endl;
    }
}
