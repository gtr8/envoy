#include "test/extensions/filters/http/ext_proc/test_processor.h"

#include "envoy/service/ext_proc/v3alpha/external_processor.pb.h"

#include "grpc++/server_builder.h"

namespace Envoy {
namespace Extensions {
namespace HttpFilters {
namespace ExternalProcessing {

void TestProcessor::start(ProcessingFunc cb) {
  wrapper_ = std::make_unique<ProcessorWrapper>(cb);
  grpc::ServerBuilder builder;
  builder.RegisterService(wrapper_.get());
  builder.AddListeningPort("127.0.0.1:0", grpc::InsecureServerCredentials(), &listening_port_);
  server_ = builder.BuildAndStart();
}

void TestProcessor::shutdown() {
  if (server_) {
    server_->Shutdown();
  }
}

} // namespace ExternalProcessing
} // namespace HttpFilters
} // namespace Extensions
} // namespace Envoy
