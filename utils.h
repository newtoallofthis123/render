#include <map>
#include <string>
#include <vector>

using namespace std;

struct Options {
  string tag;
  string content;
  vector<string> classes;
  map<string, string> attributes;
  string id;
  string style;
  string before;
  string after;
  bool extend;
};

// Simple function to parse the flags and return an options struct
static Options parse_flags(vector<string> flags) {
  Options opts{"div", "",   vector<string>(), map<string, string>(), "", "", "",
               "",    false};

  for (int i = 0; i < flags.size(); i++) {
    if (flags[i] == "-t" || flags[i] == "--tag") {
      opts.tag = flags[i + 1];
    }
    if (flags[i] == "-c" || flags[i] == "--content") {
      opts.content = flags[i + 1];
    }
    if (flags[i] == "-e" || flags[i] == "--extend") {
      opts.extend = true;
    }
    if (flags[i] == "-l" || flags[i] == "--classes") {
      auto raw_classes = flags[i + 1];
      auto classes = vector<string>();
      auto start = 0U;
      auto end = raw_classes.find(",");
      while (end != string::npos) {
        classes.push_back(raw_classes.substr(start, end - start));
        start = end + 1;
        end = raw_classes.find(",", start);
      }
      classes.push_back(raw_classes.substr(start, end));
      opts.classes = classes;
    }
    if (flags[i] == "-a" || flags[i] == "--attributes") {
      auto raw_attributes = flags[i + 1];
      auto attributes = map<string, string>();
      auto start = 0U;
      auto end = raw_attributes.find(",");
      while (end != string::npos) {
        auto pair = raw_attributes.substr(start, end - start);
        auto split = pair.find(":");
        auto key = pair.substr(0, split);
        auto value = pair.substr(split + 1);
        attributes[key] = value;
        start = end + 1;
        end = raw_attributes.find(",", start);
      }
      // parse the last pair
      auto pair = raw_attributes.substr(start, end);
      auto split = pair.find(":");
      auto key = pair.substr(0, split);
      auto value = pair.substr(split + 1);
      attributes[key] = value;
      opts.attributes = attributes;
    }
    if (flags[i] == "-i" || flags[i] == "--id") {
      opts.id = flags[i + 1];
    }
    if (flags[i] == "-s" || flags[i] == "--style") {
      opts.style = flags[i + 1];
    }
    if (flags[i] == "-b" || flags[i] == "--before") {
      opts.before = flags[i + 1];
    }
    if (flags[i] == "-a" || flags[i] == "--after") {
      opts.after = flags[i + 1];
    }
  }

  return opts;
}
