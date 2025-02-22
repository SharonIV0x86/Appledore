#pragma once

#include <exception>
#include <sstream>
#include <string>
#include <type_traits>
#include <typeinfo>

namespace Appledore {

template <typename T, typename = void>
struct is_streamable : std::false_type {};

template <typename T>
struct is_streamable<T, std::void_t<decltype(std::declval<std::ostream &>()
                                             << std::declval<const T &>())>>
    : std::true_type {};

inline std::string toString(const std::string &value) { return value; }

template <typename T>
std::enable_if_t<std::is_fundamental<T>::value ||
                     (is_streamable<T>::value && std::is_fundamental<T>::value),
                 std::string>
toString(const T &value) {
  std::ostringstream ss;
  ss << value;
  return ss.str();
}

template <typename T>
std::enable_if_t<!std::is_fundamental<T>::value || !is_streamable<T>::value,
                 std::string>
toString(const T &) {
  return std::string{"[Type: "} + typeid(T).name() + "]";
}

class GraphException : public std::exception {
public:
  explicit GraphException(std::string message)
      : m_message(std::move(message)) {}

  const char *what() const noexcept override { return m_message.c_str(); }

  const std::string &message() const { return m_message; }

private:
  std::string m_message;
};

class VertexNotFoundException : public GraphException {
public:
  template <typename T>
  explicit VertexNotFoundException(const T &vertexId)
      : GraphException(formatMessage(vertexId)),
        m_vertexId(toString(vertexId)) {}

  explicit VertexNotFoundException(const std::string &message)
      : GraphException(message), m_vertexId("[Unknown Vertex]") {}

  const std::string &vertexId() const { return m_vertexId; }

private:
  std::string m_vertexId;

  template <typename T> static std::string formatMessage(const T &id) {
    return "Vertex not found: " + toString(id);
  }
};

class EdgeNotFoundException : public GraphException {
public:
  template <typename T>
  EdgeNotFoundException(const T &source, const T &target)
      : GraphException(formatMessage(source, target)),
        m_sourceId(toString(source)), m_targetId(toString(target)) {}

  explicit EdgeNotFoundException(const std::string &message)
      : GraphException(message), m_sourceId("[Unknown]"),
        m_targetId("[Unknown]") {}

  const std::string &sourceId() const { return m_sourceId; }
  const std::string &targetId() const { return m_targetId; }

private:
  std::string m_sourceId;
  std::string m_targetId;

  template <typename T>
  static std::string formatMessage(const T &s, const T &t) {
    return "Edge not found between vertices: " + toString(s) + " -> " +
           toString(t);
  }
};

class DuplicateVertexException : public GraphException {
public:
  template <typename T>
  explicit DuplicateVertexException(const T &vertexId)
      : GraphException(formatMessage(vertexId)),
        m_vertexId(toString(vertexId)) {}

  explicit DuplicateVertexException(const std::string &message)
      : GraphException(message), m_vertexId("[Unknown Vertex]") {}

  const std::string &vertexId() const { return m_vertexId; }

private:
  std::string m_vertexId;

  template <typename T> static std::string formatMessage(const T &id) {
    return "Duplicate vertex: " + toString(id);
  }
};

class InvalidEdgeOperationException : public GraphException {
public:
  template <typename T>
  InvalidEdgeOperationException(const T &source, const T &target,
                                const std::string &reason)
      : GraphException(formatMessage(source, target, reason)),
        m_sourceId(toString(source)), m_targetId(toString(target)),
        m_reason(reason) {}

  explicit InvalidEdgeOperationException(const std::string &message)
      : GraphException(message), m_sourceId("[Unknown]"),
        m_targetId("[Unknown]"), m_reason("[Unknown]") {}

  const std::string &sourceId() const { return m_sourceId; }
  const std::string &targetId() const { return m_targetId; }
  const std::string &reason() const { return m_reason; }

private:
  std::string m_sourceId;
  std::string m_targetId;
  std::string m_reason;

  template <typename T>
  static std::string formatMessage(const T &s, const T &t,
                                   const std::string &reason) {
    std::ostringstream oss;
    oss << "Invalid edge operation between vertices: " << toString(s) << " -> "
        << toString(t) << " | Reason: " << reason;
    return oss.str();
  }
};

class GraphOperationException : public GraphException {
public:
  explicit GraphOperationException(std::string operation, std::string reason)
      : GraphException(formatMessage(operation, reason)),
        m_operation(std::move(operation)), m_reason(std::move(reason)) {}

  explicit GraphOperationException(const std::string &message)
      : GraphException(message), m_operation("[Unknown Operation]"),
        m_reason("[Unknown Reason]") {}

  const std::string &operation() const { return m_operation; }
  const std::string &reason() const { return m_reason; }

private:
  std::string m_operation;
  std::string m_reason;

  static std::string formatMessage(const std::string &op,
                                   const std::string &reason) {
    return "Graph operation '" + op + "' failed: " + reason;
  }
};

} // namespace Appledore
