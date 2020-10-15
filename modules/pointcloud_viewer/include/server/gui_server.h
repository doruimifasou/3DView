//
// Created by joseph on 2018/1/18.
//

#ifndef AUTOHDMAP_GUI_GUISERVER_HPP
#define AUTOHDMAP_GUI_GUISERVER_HPP

#include "Poco/NumericString.h"
#include "Poco/StreamCopier.h"
#include "Poco/String.h"
#include "Poco/StringTokenizer.h"
#include "Poco/Util/HelpFormatter.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/ServerApplication.h"
#include "gui_request_handler.h"
#define PCV_GUI_VERSION "pcv gui/v3.0.0_build_20180118"

class GuiRequestHandlerFactory : public HTTPRequestHandlerFactory {
 public:
  explicit GuiRequestHandlerFactory(Poco::Util::LayeredConfiguration& config) : _config(config) {}

  HTTPRequestHandler* createRequestHandler(const HTTPServerRequest& request) override {
    //
    return new GuiRequestHandler();
  }

 private:
  Poco::Util::LayeredConfiguration& _config;
};

class GuiServerApplication : public Poco::Util::ServerApplication {
 public:
  explicit GuiServerApplication(int port) : port_(port) {
    //
  }

 protected:
  void initialize(Application& self) override;

  void uninitialize() override { ServerApplication::uninitialize(); }

  int main(const std::vector<std::string>& args) override;

 private:
  std::shared_ptr<HTTPServer> http_server_ = nullptr;
  int port_;
};

class GuiServerRunnable : public Poco::Runnable {
 public:
  explicit GuiServerRunnable(int port) : port_(port) {
    argv_ = new char*[1];
    argv_[0] = (char*)"gui_server";
    gui_server_app_ = std::make_shared<GuiServerApplication>(port_);
  }
  ~GuiServerRunnable() override { delete[] argv_; }

 public:
  void run() override { gui_server_app_->run(argc_, argv_); }

 private:
  int argc_ = 1;
  char** argv_;
  int port_;
  std::shared_ptr<GuiServerApplication> gui_server_app_;
};

class GuiServer {
 public:
  explicit GuiServer(int  port) {
    gui_server_runnable = make_shared<GuiServerRunnable>(port);
  }
  ~GuiServer()=default;

 public:
  void Start() {
    thread.start(*gui_server_runnable);
  }

 private:
  Poco::Thread thread;
  shared_ptr<GuiServerRunnable> gui_server_runnable=nullptr;
};

#endif  // AUTOHDMAP_GUI_GUISERVER_HPP
