C:PeerConnectionFactory
template <class INTERNAL_CLASS>                         \
class PeerConnectionFactoryProxyWithInternal;                             \
typedef PeerConnectionFactoryProxyWithInternal<PeerConnectionFactoryInterface> PeerConnectionFactoryProxy;    \
template <class INTERNAL_CLASS>                         \
class PeerConnectionFactoryProxyWithInternal : public PeerConnectionFactoryInterface {      \
 protected:                                             \
  typedef PeerConnectionFactoryInterface C;                               \
                                                        \
 public:                                                \
  const INTERNAL_CLASS* internal() const { return c_; } \
  INTERNAL_CLASS* internal() { return c_; }
 protected:                                                              \
  PeerConnectionFactoryProxyWithInternal(rtc::Thread* signaling_thread, INTERNAL_CLASS* c) \
      : signaling_thread_(signaling_thread), c_(c) {}                    \
                                                                         \
 private:                                                                \
  mutable rtc::Thread* signaling_thread_;
 protected:                                            \
  ~PeerConnectionFactoryProxyWithInternal() {                            \
    MethodCall0<PeerConnectionFactoryProxyWithInternal, void> call(      \
        this, &PeerConnectionFactoryProxyWithInternal::DestroyInternal); \
    call.Marshal(RTC_FROM_HERE, destructor_thread());  \
  }                                                    \
                                                       \
 private:                                              \
  void DestroyInternal() { c_ = nullptr; }             \
  rtc::scoped_refptr<INTERNAL_CLASS> c_;
 public:                                                                     \
  static rtc::scoped_refptr<PeerConnectionFactoryProxyWithInternal> Create(                    \
      rtc::Thread* signaling_thread, INTERNAL_CLASS* c) {                    \
    return new rtc::RefCountedObject<PeerConnectionFactoryProxyWithInternal>(signaling_thread, \
                                                           c);               \
  }
  
private:                                                              \
  rtc::Thread* destructor_thread() const { return signaling_thread_; } \
                                                                       \
 public:  // NOLINTNEXTLINE
 using PeerConnectionFactoryInterface::CreateVideoSource;
 
 rtc::scoped_refptr<PeerConnectionInterface> CreatePeerConnection(const PeerConnectionInterface::RTCConfiguration& a1, PeerConnectionDependencies a2) override {                               \
  MethodCall2<PeerConnectionFactoryInterface, rtc::scoped_refptr<PeerConnectionInterface>, const PeerConnectionInterface::RTCConfiguration, PeerConnectionDependencies> call(c_, &PeerConnectionFactoryInterface::CreatePeerConnection, std::move(a1), \
                                 std::move(a2));                \
  return call.Marshal(RTC_FROM_HERE, signaling_thread_);        \
}