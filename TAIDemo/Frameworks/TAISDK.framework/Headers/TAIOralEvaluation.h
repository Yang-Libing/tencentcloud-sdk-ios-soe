//
//  TAIOralEvaluation.h
//  TAISDK
//
//  Created by kennethmiao on 2018/12/25.
//  Copyright © 2018年 kennethmiao. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "TAICommonParam.h"
#import "TAIError.h"

typedef NS_ENUM(NSInteger, TAIOralEvaluationWorkMode)
{
    //流式传输
    TAIOralEvaluationWorkMode_Stream = 0,
    //一次性传输
    TAIOralEvaluationWorkMode_Once,
};

typedef NS_ENUM(NSInteger, TAIOralEvaluationTextMode)
{
    //普通文本
    TAIOralEvaluationTextMode_Noraml = 0,
    //音素结构文本
    TAIOralEvaluationTextMode_Phoneme,
};


typedef NS_ENUM(NSInteger, TAIOralEvaluationEvalMode)
{
    //单词模式
    TAIOralEvaluationEvalMode_Word = 0,
    //句子模式
    TAIOralEvaluationEvalMode_Sentence,
    //段落模式
    TAIOralEvaluationEvalMode_Paragraph,
    //自由模式
    TAIOralEvaluationEvalMode_Free,
};

typedef NS_ENUM(NSInteger, TAIOralEvaluationFileType)
{
    //pcm
    TAIOralEvaluationFileType_Raw = 1,
    //wav
    TAIOralEvaluationFileType_Wav,
    //mp3
    TAIOralEvaluationFileType_Mp3,
};

typedef NS_ENUM(NSInteger, TAIOralEvaluationStorageMode)
{
    //关闭存储
    TAIOralEvaluationStorageMode_Disable = 0,
    //开启存储
    TAIOralEvaluationStorageMode_Enable,
};

typedef NS_ENUM(NSInteger, TAIOralEvaluationServerType)
{
    //英文
    TAIOralEvaluationServerType_English = 0,
    //中文
    TAIOralEvaluationServerType_Chinese,
};

@interface TAIOralEvaluationParam : TAICommonParam
//业务应用id（默认为default）
@property (nonatomic, strong) NSString *soeAppId;
//唯一标识一次评测
@property (nonatomic, strong) NSString *sessionId;
//传输模式
@property (nonatomic, assign) TAIOralEvaluationWorkMode workMode;
//评估模式
@property (nonatomic, assign) TAIOralEvaluationEvalMode evalMode;
//数据类型（内部录制仅支持mp3）
@property (nonatomic, assign) TAIOralEvaluationFileType fileType;
//音频存储
@property (nonatomic, assign) TAIOralEvaluationStorageMode storageMode;
//语言类型
@property (nonatomic, assign) TAIOralEvaluationServerType serverType;
//文本模式
@property (nonatomic, assign) TAIOralEvaluationTextMode textMode;
//苛刻指数[1.0-4.0]
@property (nonatomic, assign) float scoreCoeff;
//被评估的文本
@property (nonatomic, strong) NSString *refText;
@end


@interface TAIOralEvaluationWord : NSObject
//当前单词语音起始时间点，单位为ms
@property (nonatomic, assign) int beginTime;
//当前单词语音终止时间点，单位为ms
@property (nonatomic, assign) int endTime;
//单词发音准确度，取值范围[-1, 100]，当取-1时指完全不匹配
@property (nonatomic, assign) float pronAccuracy;
//单词发音流利度，取值范围[0, 1]
@property (nonatomic, assign) float pronFluency;
//当前词
@property (nonatomic, strong) NSString *word;
//当前词与输入语句的匹配情况，0:匹配单词、1：新增单词、2：缺少单词
@property (nonatomic, assign) int matchTag;
@end

@interface TAIOralEvaluationRet : NSObject
//唯一标识一次评测
@property (nonatomic, strong) NSString *sessionId;
//单词发音准确度，取值范围[-1, 100]，当取-1时指完全不匹配
@property (nonatomic, assign) float pronAccuracy;
//单词发音流利度，取值范围[0, 1]
@property (nonatomic, assign) float pronFluency;
//发音完整度，取值范围[0, 1]，当为词模式时，取值无意义
@property (nonatomic, assign) float pronCompletion;
//保存语音音频文件的下载地址（TAIOralEvaluationStorageMode_Enable有效）
@property (nonatomic, strong) NSString *audioUrl;
//详细发音评估结果
@property (nonatomic, strong) NSArray<TAIOralEvaluationWord *> *words;
@end

@interface TAIOralEvaluationData : NSObject
//数据seq，从1开始
@property (nonatomic, assign) NSInteger seqId;
//属否是最后分片数据
@property (nonatomic, assign) BOOL bEnd;
//音频数据
@property (nonatomic, strong) NSData *audio;
@end

@class TAIOralEvaluation;
@protocol TAIOralEvaluationDelegate <NSObject>
/**
 * 评估结果回调
 * @param oralEvaluation 评测对象
 * @param data 音频数据
 * @param result 评估结果（最后一个分片返回，其他分片为nil）
 * @param error 错误信息
 */
- (void)oralEvaluation:(TAIOralEvaluation *)oralEvaluation
        onEvaluateData:(TAIOralEvaluationData *)data
                result:(TAIOralEvaluationRet *)result
                 error:(TAIError *)error;
@end

typedef void (^TAIOralEvaluationCallback)(TAIError *error);

@interface TAIOralEvaluation : NSObject
/**
 * 录制数据回调
 */
@property (nonatomic, weak) id<TAIOralEvaluationDelegate> delegate;
/**
 * 开始录制和评测
 * @param param 参数（内部录制仅支持mp3）
 * @param callback 回调
 */
- (void)startRecordAndEvaluation:(TAIOralEvaluationParam *)param callback:(TAIOralEvaluationCallback)callback;
/**
 * 结束录制和评测
 * @param callback 回调
 */
- (void)stopRecordAndEvaluation:(TAIOralEvaluationCallback)callback;
/**
 * 属否正在录制
 * @return BOOL 是否录制
 */
- (BOOL)isRecording;
/**
 * 设置分片大小，建议为1024的整数倍，默认为1024*10
 * @param size 分片大小
 */
- (void)setFragSize:(NSInteger)size;
/**
 * 口语评测（外部录制）
 * @param param 参数
 * @param data 音频数据（三种格式目前仅支持16k采样率16bit编码单声道，如有不一致可能导致评估不准确或失败）
 * @param callback 回调
 */
- (void)oralEvaluation:(TAIOralEvaluationParam *)param data:(TAIOralEvaluationData *)data callback:(TAIOralEvaluationCallback)callback;
/**
 * 获取签名所需字符串
 * @param timestamp 时间戳
 * @return NSString 签名
 */
- (NSString *)getStringToSign:(NSInteger)timestamp;
@end
