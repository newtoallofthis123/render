#include "node.h"
#include <map>
#include <ostream>

namespace Option {
enum {
  id = 0,
  tag,
  attributes,
  classes,
  properties,
  content,
  data,
  context,
  binding,
  component,
  service,
  message
};
}
static ProcUnit ActiveRenderCount = 0;

template <Stream stream> class XML : public Node<stream> {
public:
  ProcUnit RenderID;
  std::string tag, id, content;
  std::map<std::string, std::string> attributes;
  std::vector<std::string> classes;
  std::vector<XML *> nodes;

  inline const void SetRenderID() {
    RenderID = ActiveRenderCount;
    ++ActiveRenderCount;
  }

  XML(const std::string &_tag) throw() : tag(_tag) { XML::SetRenderID(); }
  XML(const std::string &_tag, const std::string &_id)
  throw() : tag(_tag), id(_id) { XML::SetRenderID(); }
  XML(const std::string &_tag, const std::string &_id,
      std::vector<std::string> &_classes)
  throw() : tag(_tag), id(_id), classes(_classes) { XML::SetRenderID(); }
  XML(const std::string &_tag, const std::string &_id,
      std::vector<std::string> &_classes,
      std::map<std::string, std::string> &_attributes)
  throw() : tag(_tag), id(_id), classes(_classes), attributes(_attributes) {
    XML::SetRenderID();
  }

  XML(const std::string &_tag, std::map<ProcUnit, void *> options)
  throw() : tag(_tag) {
    XML::SetRenderID();
    SetOptions(options);
  }
  XML(const std::string &_tag, const std::string &_id,
      std::map<ProcUnit, void *> options)
  throw() : tag(_tag), id(_id) {
    XML::SetRenderID();
    SetOptions(options);
  }
  XML(const std::string &_tag, const std::string &_id,
      std::vector<std::string> &_classes, std::map<ProcUnit, void *> options)
  throw() : tag(_tag), id(_id), classes(_classes) {
    XML::SetRenderID();
    SetOptions(options);
  }
  XML(const std::string &_tag, const std::string &_id,
      std::vector<std::string> &_classes,
      std::map<std::string, std::string> &_attributes,
      std::map<ProcUnit, void *> options)
  throw() : tag(_tag), id(_id), classes(_classes), attributes(_attributes) {
    XML::SetRenderID();
    SetOptions(options);
  }

  void SetOptions(std::map<ProcUnit, void *> options) {
    std::map<ProcUnit, void *>::iterator option;
    for (option = options.begin(); option != options.end(); ++option) {
      switch (option->first) {
      case Option::tag:
        tag = *(std::string *)option->second;
        break;
      case Option::id:
        id = *(std::string *)option->second;
        break;
      case Option::classes:
        classes = *(std::vector<std::string> *)(option->second);
        break;
      case Option::attributes:
        attributes = *(std::map<std::string, std::string> *)(option->second);
        break;
      default:
        break;
      }
    }
  }

  inline void operator<<(XML *object) {
    this->nodes.push_back(static_cast<XML *>(object));
  }

  inline void operator<<(XML &object) {
    this->nodes.push_back(static_cast<XML *>(&object));
  }

  inline XML operator[](unsigned int i) const {
    if (i >= this->nodes.size()) {
      throw std::out_of_range("Index out of range");
    }
    return *this->nodes[i];
  }

  inline XML &operator[](unsigned int i) {
    if (i >= this->nodes.size()) {
      throw std::out_of_range("Index out of range");
    }
    return *this->nodes[i];
  }

  inline void render(stream &outputstream) {
    RenderHead(outputstream);
    RenderCorpus(outputstream);
    RenderTail(outputstream);
  }

  inline void RenderHead(stream &outputstream) {
    outputstream << std::endl << "<";
    if (!this->id.empty())
      outputstream << this->tag << " id=\"" << this->id << "\"";
    else
      outputstream << this->tag;

    if (!this->attributes.empty()) {
      for (std::map<std::string, std::string>::const_iterator attribute =
               this->attributes.begin();
           attribute != this->attributes.end(); ++attribute) {
        outputstream << " " << attribute->first << "=\"" << attribute->second
                     << "\"";
      }
    }
    outputstream << ">";

    if (!this->content.empty())
      outputstream << std::endl << this->content << std::endl;
  }

  inline void RenderCorpus(stream &outputstream) {
    if (!this->nodes.empty())
      for (ProcUnit i = 0, L = this->nodes.size(); i < L; ++i) {
        outputstream << *this->nodes[i];
      }
  }

  inline void RenderTail(stream &outputstream) {
    outputstream << std::endl << "</" << this->tag << ">";
  }

  inline void operator>>(stream &outputstream) { render(outputstream); }

  inline friend stream &operator<<(stream &outputstream, XML &obj) {
    obj.render(outputstream);
    return outputstream;
  }
};
