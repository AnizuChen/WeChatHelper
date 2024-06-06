# 微信 PC Hook软件 微信PC协议

## 概述

本项目通过注入微信程序，提供一系列HTTP接口，允许用户通过这些接口与微信功能进行交互。 个人项目精力有限，欢迎 follow star！

## 支持版本

目前支持 3.9.10.27

## 功能

- 注入微信（wxhelper）
- 提供各种微信功能的HTTP接口
- 使用方便，易于与其他系统集成
- 大部分接口已经满足需求，剩下部分接口还在开发

### API端点

以下是一些可用的端点：

```
/api/netscene/createchatroom
/api/netscene/getmemberfromchatroom
/api/wechat/getchatroomdetailinfo
/api/wechat/addmembertchatroom
/api/wechat/invitemembertochatroom
/api/wechat/delmemberfromchatroom
/api/wechat/quitanddelchatroom
/api/wechat/modchatroomtopic
/api/wechat/modchatroommembernickname
/api/wechat/setchatroomannouncement
/api/netscene/getcontact
/api/netscene/searchcontact
/api/netscene/addcontact
/api/netscene/verifyapply
/api/netscene/getcontactlabellist
/api/netscene/addcontactlabel
/api/wechat/delcontact
/api/wechat/getcontact
/api/wechat/getcontactlist
/api/wechat/remarkcontact
/api/wechat/blackcontact
/api/wechat/delcontactlabel
/api/wechat/modifycontactlabel
/api/netscene/getA8key
/api/wechat/cdndownload
/api/wechat/cdnupload
/api/wechat/getselfinfo
/api/wechat/sendtextmsg
/api/wechat/sendimagemsg
/api/wechat/sendfilemsg
/api/wechat/sendpatmsg
/api/wechat/sendcardmsg
/api/wechat/setmessagenotify
api/netscene/timelinegetfirstpage
/api/netscene/timelinegetnextpage
/api/netscene/snsobjectdetail
/api/wechat/snsobjectlike
/api/wechat/snsobjectunlike
/api/wechat/snsobjectdocomment
/api/wechat/snsobjectdelcomment
```

### 关于

netscence路径的接口是带协议返回
wechat路径协议不带协议返回

框架实现自动注入点，同时实现微信协议返回包拦截注入

##### Q&A : 为啥不能HOOK 请求协议？

一、是找到的协议版本较远，请求协议如果少字段容易被被服务器知道
二、还有就是大部分请求协议字段较多，发起请求直接call函数传参较少难度低
三、有没有需要自己构造请求数据包，看情况，比如PC微信不支持查看用户朋友圈以及发圈，如果要实现就需要自己这样处理

##### Q&A : 关于日志？

目前没有加运行日志，主要因为大部分日志框架都是多线程，很多都是用c++11 thread 这在DLL  Dettach的时候很容易卡死。直接用微信里面的日志接口把日志打到微信里面应该是可以的。

## TODO

- 部分接口完善
- HOOK隐藏
- 微信消息回调优化
- 微信协议DUMP

## 贡献
欢迎贡献！请提出issue或提交pull request。

## 捐赠 （USDT-TRC20）
```
TB7ReYEVZcNLDcKL71gu7aqMQ3h8CyYkMM
```

## 许可证

本项目使用MIT许可证。详情请参阅LICENSE文件。

## 声明
本软件仅供教育和研究用途。请自行承担使用风险。作者不对任何滥用本软件的行为负责。

## 加入电报群
为了获得更多支持和交流机会，请加入电报群：[Telegram群链接](https://t.me/wechatopensource)



