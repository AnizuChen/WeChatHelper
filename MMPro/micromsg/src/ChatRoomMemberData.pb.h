// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ChatRoomMemberData.proto

#ifndef PROTOBUF_ChatRoomMemberData_2eproto__INCLUDED
#define PROTOBUF_ChatRoomMemberData_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3003000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3003000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
#include "ChatRoomMemberInfo.pb.h"
// @@protoc_insertion_point(includes)
namespace MMPro {
namespace micromsg {
class ChatRoomMemberData;
class ChatRoomMemberDataDefaultTypeInternal;
extern ChatRoomMemberDataDefaultTypeInternal _ChatRoomMemberData_default_instance_;
class ChatRoomMemberInfo;
class ChatRoomMemberInfoDefaultTypeInternal;
extern ChatRoomMemberInfoDefaultTypeInternal _ChatRoomMemberInfo_default_instance_;
}  // namespace micromsg
}  // namespace MMPro

namespace MMPro {
namespace micromsg {

namespace protobuf_ChatRoomMemberData_2eproto {
// Internal implementation detail -- do not call these.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[];
  static const ::google::protobuf::uint32 offsets[];
  static void InitDefaultsImpl();
  static void Shutdown();
};
void AddDescriptors();
void InitDefaults();
}  // namespace protobuf_ChatRoomMemberData_2eproto

// ===================================================================

class ChatRoomMemberData : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:MMPro.micromsg.ChatRoomMemberData) */ {
 public:
  ChatRoomMemberData();
  virtual ~ChatRoomMemberData();

  ChatRoomMemberData(const ChatRoomMemberData& from);

  inline ChatRoomMemberData& operator=(const ChatRoomMemberData& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const ChatRoomMemberData& default_instance();

  static inline const ChatRoomMemberData* internal_default_instance() {
    return reinterpret_cast<const ChatRoomMemberData*>(
               &_ChatRoomMemberData_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    0;

  void Swap(ChatRoomMemberData* other);

  // implements Message ----------------------------------------------

  inline ChatRoomMemberData* New() const PROTOBUF_FINAL { return New(NULL); }

  ChatRoomMemberData* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const ChatRoomMemberData& from);
  void MergeFrom(const ChatRoomMemberData& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(ChatRoomMemberData* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // repeated .MMPro.micromsg.ChatRoomMemberInfo _ChatRoomMember = 2;
  int _chatroommember_size() const;
  void clear__chatroommember();
  static const int kChatRoomMemberFieldNumber = 2;
  const ::MMPro::micromsg::ChatRoomMemberInfo& _chatroommember(int index) const;
  ::MMPro::micromsg::ChatRoomMemberInfo* mutable__chatroommember(int index);
  ::MMPro::micromsg::ChatRoomMemberInfo* add__chatroommember();
  ::google::protobuf::RepeatedPtrField< ::MMPro::micromsg::ChatRoomMemberInfo >*
      mutable__chatroommember();
  const ::google::protobuf::RepeatedPtrField< ::MMPro::micromsg::ChatRoomMemberInfo >&
      _chatroommember() const;

  // required uint32 _MemberCount = 1;
  bool has__membercount() const;
  void clear__membercount();
  static const int kMemberCountFieldNumber = 1;
  ::google::protobuf::uint32 _membercount() const;
  void set__membercount(::google::protobuf::uint32 value);

  // optional uint32 _InfoMask = 3;
  bool has__infomask() const;
  void clear__infomask();
  static const int kInfoMaskFieldNumber = 3;
  ::google::protobuf::uint32 _infomask() const;
  void set__infomask(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:MMPro.micromsg.ChatRoomMemberData)
 private:
  void set_has__membercount();
  void clear_has__membercount();
  void set_has__infomask();
  void clear_has__infomask();

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable int _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::MMPro::micromsg::ChatRoomMemberInfo > _chatroommember_;
  ::google::protobuf::uint32 _membercount_;
  ::google::protobuf::uint32 _infomask_;
  friend struct protobuf_ChatRoomMemberData_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// ChatRoomMemberData

// required uint32 _MemberCount = 1;
inline bool ChatRoomMemberData::has__membercount() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ChatRoomMemberData::set_has__membercount() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ChatRoomMemberData::clear_has__membercount() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ChatRoomMemberData::clear__membercount() {
  _membercount_ = 0u;
  clear_has__membercount();
}
inline ::google::protobuf::uint32 ChatRoomMemberData::_membercount() const {
  // @@protoc_insertion_point(field_get:MMPro.micromsg.ChatRoomMemberData._MemberCount)
  return _membercount_;
}
inline void ChatRoomMemberData::set__membercount(::google::protobuf::uint32 value) {
  set_has__membercount();
  _membercount_ = value;
  // @@protoc_insertion_point(field_set:MMPro.micromsg.ChatRoomMemberData._MemberCount)
}

// repeated .MMPro.micromsg.ChatRoomMemberInfo _ChatRoomMember = 2;
inline int ChatRoomMemberData::_chatroommember_size() const {
  return _chatroommember_.size();
}
inline void ChatRoomMemberData::clear__chatroommember() {
  _chatroommember_.Clear();
}
inline const ::MMPro::micromsg::ChatRoomMemberInfo& ChatRoomMemberData::_chatroommember(int index) const {
  // @@protoc_insertion_point(field_get:MMPro.micromsg.ChatRoomMemberData._ChatRoomMember)
  return _chatroommember_.Get(index);
}
inline ::MMPro::micromsg::ChatRoomMemberInfo* ChatRoomMemberData::mutable__chatroommember(int index) {
  // @@protoc_insertion_point(field_mutable:MMPro.micromsg.ChatRoomMemberData._ChatRoomMember)
  return _chatroommember_.Mutable(index);
}
inline ::MMPro::micromsg::ChatRoomMemberInfo* ChatRoomMemberData::add__chatroommember() {
  // @@protoc_insertion_point(field_add:MMPro.micromsg.ChatRoomMemberData._ChatRoomMember)
  return _chatroommember_.Add();
}
inline ::google::protobuf::RepeatedPtrField< ::MMPro::micromsg::ChatRoomMemberInfo >*
ChatRoomMemberData::mutable__chatroommember() {
  // @@protoc_insertion_point(field_mutable_list:MMPro.micromsg.ChatRoomMemberData._ChatRoomMember)
  return &_chatroommember_;
}
inline const ::google::protobuf::RepeatedPtrField< ::MMPro::micromsg::ChatRoomMemberInfo >&
ChatRoomMemberData::_chatroommember() const {
  // @@protoc_insertion_point(field_list:MMPro.micromsg.ChatRoomMemberData._ChatRoomMember)
  return _chatroommember_;
}

// optional uint32 _InfoMask = 3;
inline bool ChatRoomMemberData::has__infomask() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void ChatRoomMemberData::set_has__infomask() {
  _has_bits_[0] |= 0x00000002u;
}
inline void ChatRoomMemberData::clear_has__infomask() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void ChatRoomMemberData::clear__infomask() {
  _infomask_ = 0u;
  clear_has__infomask();
}
inline ::google::protobuf::uint32 ChatRoomMemberData::_infomask() const {
  // @@protoc_insertion_point(field_get:MMPro.micromsg.ChatRoomMemberData._InfoMask)
  return _infomask_;
}
inline void ChatRoomMemberData::set__infomask(::google::protobuf::uint32 value) {
  set_has__infomask();
  _infomask_ = value;
  // @@protoc_insertion_point(field_set:MMPro.micromsg.ChatRoomMemberData._InfoMask)
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)


}  // namespace micromsg
}  // namespace MMPro

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_ChatRoomMemberData_2eproto__INCLUDED