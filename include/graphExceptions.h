#pragma once

#include <exception>
#include <string>
#include <sstream>
#include <type_traits>

namespace Appledore {

    // Base class for all graph-related exceptions
    class GraphException : public std::exception {
    public:
        explicit GraphException(const std::string& message)
            : m_message(message) 
        {
        }

        const char* what() const noexcept override {
            return m_message.c_str();
        }

    protected:
        std::string m_message;

        // Helper to convert any vertex type to string
        template<typename T>
        static std::string toString(const T& value) {
            if constexpr (std::is_same_v<T, std::string>) {
                return value;
            } else {
                std::ostringstream ss;
                ss << value;
                return ss.str();
            }
        }
    };

    // Thrown when attempting to access a non-existent vertex
    class VertexNotFoundException : public GraphException {
    public:
        template<typename T>
        explicit VertexNotFoundException(const T& vertexId)
            : GraphException("Vertex not found: " + toString(vertexId))
        {
        }

        explicit VertexNotFoundException(const std::string& message)
            : GraphException(message)
        {
        }
    };

    // Thrown when an operation targets a non-existent edge
    class EdgeNotFoundException : public GraphException {
    public:
        template<typename T>
        EdgeNotFoundException(const T& source, const T& target)
            : GraphException("Edge not found between vertices: " + 
                           toString(source) + " -> " + toString(target))
        {
        }

        explicit EdgeNotFoundException(const std::string& message)
            : GraphException(message)
        {
        }
    };

    // Thrown when adding a vertex that already exists
    class DuplicateVertexException : public GraphException {
    public:
        template<typename T>
        explicit DuplicateVertexException(const T& vertexId)
            : GraphException("Duplicate vertex: " + toString(vertexId))
        {
        }

        explicit DuplicateVertexException(const std::string& message)
            : GraphException(message)
        {
        }
    };

    // Thrown for invalid operations on edges (e.g., adding edge between non-existent vertices)
    class InvalidEdgeOperationException : public GraphException {
    public:
        template<typename T>
        InvalidEdgeOperationException(const T& source, const T& target, 
                                    const std::string& reason)
            : GraphException("Invalid edge operation between vertices " + 
                           toString(source) + " -> " + toString(target) +
                           ": " + reason)
        {
        }

        explicit InvalidEdgeOperationException(const std::string& message)
            : GraphException(message)
        {
        }
    };

    // Generic exception for unexpected graph operations
    class GraphOperationException : public GraphException {
    public:
        explicit GraphOperationException(const std::string& operation, 
                                       const std::string& reason)
            : GraphException("Graph operation '" + operation + "' failed: " + reason)
        {
        }

        explicit GraphOperationException(const std::string& message)
            : GraphException(message)
        {
        }
    };

} // namespace Appledore
