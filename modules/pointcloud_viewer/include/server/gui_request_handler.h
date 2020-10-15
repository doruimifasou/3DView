//
// Created by joseph on 2018/1/18.
//

#ifndef PCV_GUI_GLMAPREQUESTHANDLER_HPP
#define PCV_GUI_GLMAPREQUESTHANDLER_HPP
#include <string>
//
#include <Poco/JSON/Object.h>
#include "Poco/Net/HTTPServer.h"
#include "Poco/Net/PartHandler.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/HTMLForm.h"
#include "Poco/Net/MessageHeader.h"
#include "Poco/Timestamp.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/Exception.h"
#include "Poco/ThreadPool.h"

using Poco::Net::ServerSocket;
using Poco::Net::HTTPRequestHandler;
using Poco::Net::HTTPRequestHandlerFactory;
using Poco::Net::HTTPServer;
using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPServerResponse;
using Poco::Net::HTTPResponse;
using Poco::Net::HTTPServerParams;
using Poco::Net::NameValueCollection;
using Poco::Net::HTMLForm;
using Poco::Net::MessageHeader;
using Poco::Timestamp;
using Poco::DateTimeFormatter;
using Poco::DateTimeFormat;
using Poco::ThreadPool;

using namespace std;

class GuiRequestHandler : public Poco::Net::HTTPRequestHandler {
public:
    /**
     * 处理请求
     * @param request
     * @param response
     */
    void handleRequest(HTTPServerRequest &request, HTTPServerResponse &response) override;
protected:
    void DoResource(HTTPServerRequest &request, HTTPServerResponse &response);
    void DoPointClouds(HTTPServerRequest &request, HTTPServerResponse &response);
};


#endif //PCV_GUI_GLMAPREQUESTHANDLER_HPP
