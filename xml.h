#include "node.h"
#include <map>

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

template <Stream stream> class XML : public Node<stream> {
private:
  static ProcUnit ActiveRenderCount;

public:
  ProcUnit RenderID;
  std::string tag, id, content;
  std::map<std::string, std::string> attributes;
  std::vector<std::string> classes;
  std::vector<XML *> children;

  inline const void SetRenderID() {
    RenderID = ActiveRenderCount;
    ++ActiveRenderCount;
  }

  XML(const std::string &_tag) throw() : tag(_tag) {}

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
    this->children.push_back(static_cast<XML *>(object));
  }

  inline void operator<<(XML &object) {
    this->children.push_back(static_cast<XML *>(&object));
  }

  inline void RenderHead(std::ostream &outputstream) {
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

  inline void RenderCorpus(std::ostream &outputstream) {
    if (!this->children.empty())
      for (ProcUnit i = 0, L = this->children.size(); i < L; ++i) {
        outputstream << *this->children[i];
      }
  }

  inline void RenderTail(std::ostream &outputstream) {
    outputstream << std::endl << "</" << this->tag << ">";
  }

  inline void operator>>(std::ostream &outputstream) {
    this->render(outputstream);
  }

  inline friend std::ostream &operator<<(std::ostream &outputstream, XML &obj) {
    obj.render(outputstream);
    return outputstream;
  }
};
