#ifndef LABELMANAGER_H
#define LABELMANAGER_H

#include <unordered_map>
#include <string>
#include "asmjit/asmjit.h"
#include "SignalHandler.h"

class LabelManager {
public:
    // No dependency injection through constructor — more flexible
    LabelManager() = default;

    // Creates a new unnamed label
    static asmjit::Label createUnnamedLabel(asmjit::x86::Assembler &assembler) {
        return assembler.newLabel();
    }

    // Creates a named label
    asmjit::Label createLabel(asmjit::x86::Assembler &assembler, const std::string &name) {
        if (_labels.find(name) != _labels.end()) {
            std::cout << "LabelManager: Label name already exists: " << name;
            return _labels[name];
        }

        if (!assembler.isInitialized()) {
            SignalHandler::instance().raise(21);
        }

        asmjit::Label lbl = assembler.newLabel();
        _labels[name] = lbl;
        return lbl;
    }

    // Retrieve a label by name
    asmjit::Label getLabel(const std::string &name) const {
        auto it = _labels.find(name);
        if (it == _labels.end()) {
            std::cerr << ("LabelManager: Label not found: " + name);
            SignalHandler::instance().raise(21);
        }
        return it->second;
    }

    // Bind a label to the current position and add a comment
    void bindLabel(asmjit::x86::Assembler &assembler, const std::string &name) const {
        auto it = _labels.find(name);
        if (it == _labels.end()) {
            std::cerr << "LabelManager: Attempting to bind unknown label: " << name;
            return;
        }

        // Add an assembler-style comment for readability
        assembler.comment(("; -- " + name).c_str());

        // Bind the label
        assembler.bind(it->second);
    }

    // Jump to a label (supports conditional and unconditional jumps)
    void jump(asmjit::x86::Assembler &assembler, const std::string &name) const {
        auto it = _labels.find(name);
        if (it == _labels.end()) {
            std::cerr << "LabelManager: Attempting to jump to unknown label: " << name;
            SignalHandler::instance().raise(21);

        }
        assembler.jmp(it->second);
    }

    void jmp(asmjit::x86::Assembler &assembler, const std::string &name) const {
        auto it = _labels.find(name);
        if (it == _labels.end()) {
            std::cerr << "LabelManager: Attempting to jump to unknown label: " << name;
            SignalHandler::instance().raise(21);
        }
        assembler.jmp(it->second);
    }

    void jne(asmjit::x86::Assembler &assembler, const std::string &name) const {
        auto it = _labels.find(name);
        if (it == _labels.end()) {
            std::cerr << "LabelManager: Attempting to jump to unknown label: " << name;
            SignalHandler::instance().raise(21);
        }
        assembler.jne(it->second);
    }

    void je(asmjit::x86::Assembler &assembler, const std::string &name) const {
        auto it = _labels.find(name);
        if (it == _labels.end()) {
            std::cerr << "LabelManager: Attempting to jump to unknown label: " << name;
            SignalHandler::instance().raise(21);
        }
        assembler.je(it->second);
    }

    void js(asmjit::x86::Assembler &assembler, const std::string &name) const {
        auto it = _labels.find(name);
        if (it == _labels.end()) {
            std::cerr << "LabelManager: Attempting to jump to unknown label: " << name;
            SignalHandler::instance().raise(21);
        }
        assembler.js(it->second);
    }




    void jz(asmjit::x86::Assembler &assembler, const std::string &name) const {
        auto it = _labels.find(name);
        if (it == _labels.end()) {
            std::cerr << "LabelManager: Attempting to jump to unknown label: " << name;
            SignalHandler::instance().raise(21);
        }
        assembler.jz(it->second);
    }


    void jb(asmjit::x86::Assembler &assembler, const std::string &name) const {
        auto it = _labels.find(name);
        if (it == _labels.end()) {
            std::cerr << "LabelManager: Attempting to jump to unknown label: " << name;
            SignalHandler::instance().raise(21);
        }
        assembler.jb(it->second);
    }

    void jnz(asmjit::x86::Assembler &assembler, const std::string &name) const {
        auto it = _labels.find(name);
        if (it == _labels.end()) {
            std::cerr << "LabelManager: Attempting to jump to unknown label: " << name;
            SignalHandler::instance().raise(21);
        }
        assembler.jnz(it->second);
    }

    void jl(asmjit::x86::Assembler &assembler, const std::string &name) const {
        auto it = _labels.find(name);
        if (it == _labels.end()) {
            std::cerr << "LabelManager: Attempting to jump to unknown label: " << name;
            SignalHandler::instance().raise(21);
        }
        assembler.jl(it->second);
    }


    void jle(asmjit::x86::Assembler &assembler, const std::string &name) const {
        auto it = _labels.find(name);
        if (it == _labels.end()) {
            std::cerr << "LabelManager: Attempting to jump to unknown label: " << name;
            SignalHandler::instance().raise(21);
        }
        assembler.jle(it->second);
    }

    void jg(asmjit::x86::Assembler &assembler, const std::string &name) const {
        auto it = _labels.find(name);
        if (it == _labels.end()) {
            std::cerr << "LabelManager: Attempting to jump to unknown label: " << name;
            SignalHandler::instance().raise(21);
        }
        assembler.jg(it->second);
    }


    void jge(asmjit::x86::Assembler &assembler, const std::string &name) const {
        auto it = _labels.find(name);
        if (it == _labels.end()) {
            std::cerr << "LabelManager: Attempting to jump to unknown label: " << name;
            SignalHandler::instance().raise(21);
        }
        assembler.jge(it->second);
    }

    void call(asmjit::x86::Assembler &assembler, const std::string &name) const {
        auto it = _labels.find(name);
        if (it == _labels.end()) {
            std::cerr << "LabelManager: Attempting to jump to unknown label: " << name;
            SignalHandler::instance().raise(21);
        }
        assembler.call(it->second);
    }

    void clearLabels() {
        _labels.clear();
    }



private:
    std::unordered_map<std::string, asmjit::Label> _labels; // Labels storage
};

#endif // LABELMANAGER_H