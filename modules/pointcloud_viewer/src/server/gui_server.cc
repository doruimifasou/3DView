//
// Created by joseph on 2018/1/18.
//
#include "server/gui_server.h"

#include <string>

using namespace std;

void GuiServerApplication::initialize(Application &self) {
  loadConfiguration();
  //
  ServerApplication::initialize(self);
}

int GuiServerApplication::main(const std::vector<std::string> &args) {
  unsigned short port = (unsigned short)config().getInt("port", port_);
  int maxThreads = config().getInt("maxthreads", 4);
  int maxQueued = config().getInt("maxqueued", 512);
  //
  bool keepalive = config().getBool("keepalive", false);
  int keepalive_timeout = config().getInt("keepalive.timeout", 10);
  int keepalive_maxreqs = config().getInt("keepalive.maxreqs", 0);
  int timeout = config().getInt("timeout", 60);
  //
  //
  ServerSocket svs(port);

  //
  ThreadPool threadPool(maxThreads, maxThreads, 60, 0);
  //
  auto *pHTTPServerParams = new HTTPServerParams();
  pHTTPServerParams->setMaxQueued(maxQueued);
  pHTTPServerParams->setKeepAlive(keepalive);
  pHTTPServerParams->setSoftwareVersion(PCV_GUI_VERSION);
  if (keepalive) {
    Poco::Timespan tspan(keepalive_timeout, 0);
    pHTTPServerParams->setKeepAliveTimeout(tspan);
    pHTTPServerParams->setMaxKeepAliveRequests(keepalive_maxreqs);
  }
  Poco::Timespan tspan_timeout(timeout, 0);
  pHTTPServerParams->setTimeout(tspan_timeout);
  //
  auto *phandler_factory = new GuiRequestHandlerFactory(config());
  http_server_ = std::make_shared<HTTPServer>(phandler_factory, threadPool, svs, pHTTPServerParams);
  //
  http_server_->start();
  //
  this->logger().information("gui server started at port=" + to_string(port));
  //
  waitForTerminationRequest();
  http_server_->stop();
  return Application::EXIT_OK;
}