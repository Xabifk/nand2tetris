#include <bits/stdc++.h>

class Parser
{
public:
  enum commandTypes
  {
    eC_COMMAND, eA_COMMAND, eL_COMMAND
  };

  commandTypes commandType()
  {
    if(m_current_command[0]=='@') return eA_COMMAND;
    if(m_current_command[0]=='(' && m_current_command[m_current_command.size()-1]) return eL_COMMAND;
    return eC_COMMAND;
  }

  bool hasMoreCommands()
  {
    return !m_fin.eof();
  }

  bool setInput(std::string _input_file)
  {
    if(m_fin = std::ifstream(_input_file))
    {
      return true;
    }
    else
    {
      return false;
    }
  }

  bool advance()
  {
    if(hasMoreCommands())
    {
      std::getline(m_fin, m_current_command);

      std::string delimiter = " ";
      int pos;

      while((pos = m_current_command.find(delimiter)) != std::string::npos)
      {
        m_current_command.erase(m_current_command.begin()+pos);
      }

      return true;
    }
    else
    {
      return false;
    }
  }

  std::string symbol()
  {
    std::string _symbol = m_current_command;

    switch (commandType())
    {
      case eA_COMMAND:
        _symbol.erase(_symbol.front());
        break;
      case eL_COMMAND:
        _symbol.erase(_symbol.back());
        _symbol.erase(_symbol.front());
        break;
      default:
        _symbol = "ERROR";
        break;
    }

    return _symbol;

  }

  std::string dest()
  {
    if(commandType() != eC_COMMAND)
    {
      return "ERROR";
    }

    std::string _dest = m_current_command;

    std::string delimiter = "=";
    int pos;

    if((pos = _dest.find(delimiter)) != std::string::npos)
    {
      _dest = _dest.substr(0, pos);
    }
    else
    {
      _dest = "";
    }

    return _dest;
  }

  std::string comp()
  {
    if(commandType() != eC_COMMAND)
    {
      return "ERROR";
    }

    std::string _comp = m_current_command;

    std::string delimetir_left = "=", delimiter_right = ";";
    int pos;

    if((pos = _comp.find(delimiter_right)) != std::string::npos)
    {
      _comp = _comp.substr(0, pos);
    }

    if((pos = _comp.find(delimetir_left)) != std::string::npos)
    {
      _comp = _comp.substr(pos+delimetir_left.size());
    }

    return _comp;
  }

  std::string jump()
  {
    if(commandType() != eC_COMMAND)
    {
      return "ERROR";
    }

    std::string _jump = m_current_command;

    std::string delimiter = ";";
    int pos;

    if((pos = _jump.find(delimiter)) != std::string::npos)
    {
      _jump = _jump.substr(pos+delimiter.size());
    }
    else
    {
      _jump = "";
    }

    return _jump;

  }

  Parser()
  {}

  Parser(std::string _input_file)
  {
    setInput(_input_file);
  }

  ~Parser()
  {}
private:

  std::ifstream m_fin;

  std::string m_current_command;

};

int main(int argc, char *argv[])
{
  if(argc != 2)
  {
    std::cerr<<"Usage: "<<argv[0]<<" <asm file>\n";
    exit(1);
  }

}
