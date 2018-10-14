#include <bits/stdc++.h>

class Parser
{
public:
  enum commandTypes
  {
    eC_COMMAND, eA_COMMAND, eL_COMMAND, eCOMMENT, eEMPTY
  };

  commandTypes commandType()
  {
    if(m_current_command.front() == '@') return eA_COMMAND;
    if(m_current_command.front() == '(' && m_current_command.back() == ')') return eL_COMMAND;
    if(m_current_command.front() == '/') return eCOMMENT;
    if(m_current_command == "" || m_current_command == "\r\n") return eEMPTY;
    if(m_current_command.find('=') != std::string::npos || m_current_command.find(';') != std::string::npos) return eC_COMMAND;
    return eEMPTY;
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

      int pos;

      while((pos = m_current_command.find(' ')) != std::string::npos)
      {
        m_current_command.erase(m_current_command.begin()+pos);
      }

      while((pos = m_current_command.find((char)(13))) != std::string::npos)
      {
        m_current_command.erase(m_current_command.begin()+pos);
      }

      while((pos = m_current_command.find((char)(10))) != std::string::npos)
      {
        m_current_command.erase(m_current_command.begin()+pos);
      }

      for(int i=1; i < m_current_command.length(); i++)
      {
        if(m_current_command[i-1] == '/' && m_current_command[i] == '/')
        {
          m_current_command.erase(m_current_command.begin()+i-1, m_current_command.end());
          break;
        }
      }

      //std::cout<<m_current_command<<'\n';

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
        _symbol.erase(_symbol.begin());
        break;
      case eL_COMMAND:
        _symbol.erase(_symbol.end()-1);
        _symbol.erase(_symbol.begin());
        break;
      default:
        _symbol = "ERROR";
        break;
    }
    // debug
    //std::cout<<_symbol<<'\n';

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

  int getLineNr()
  {
    return m_line_nr;
  }

  void increment()
  {
    m_line_nr++;
  }

  void reset()
  {
    m_fin.clear();
    m_fin.seekg(0, std::ios::beg);
    m_line_nr = 0;
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

  int m_line_nr = 0;
};

class Code
{          // TODO make this work how it's supposed to, I don't want to read the ALU specifiacation now
public:
  std::string dest(std::string _dest)
  {
    std::string mask(3, '0');

    if(_dest.find("A") != std::string::npos)
    {
      mask[0] = '1';
    }
    if(_dest.find("D") != std::string::npos)
    {
      mask[1] = '1';
    }
    if(_dest.find("M") != std::string::npos)
    {
      mask[2] = '1';
    }

    return mask;
  }

  std::string jump(std::string _jump)
  {
    std::string mask = "000";

    if(_jump == "JGT")
    {
      mask = "001";
    }
    if(_jump == "JEQ")
    {
      mask = "010";
    }if(_jump == "JGE")
    {
      mask = "011";
    }if(_jump == "JLT")
    {
      mask = "100";
    }if(_jump == "JNE")
    {
      mask = "101";
    }if(_jump == "JLE")
    {
      mask = "110";
    }
    if(_jump == "JMP")
    {
      mask = "111";
    }

    return mask;
  }

  std::string comp(std::string _comp)
  {
    std::string mask;

    if(_comp == "0")
    {
      mask = "101010";
    } else
    if(_comp == "1")
    {
      mask = "111111";
    } else
    if(_comp == "-1")
    {
      mask = "111010";
    } else
    if(_comp == "D")
    {
      mask = "001100";
    } else
    if(_comp == "A" || _comp == "M")
    {
      mask = "110000";
    } else
    if(_comp == "!D")
    {
      mask = "001101";
    } else
    if(_comp == "!A" || _comp == "!M")
    {
      mask = "110001";
    } else
    if(_comp == "-D")
    {
      mask = "001111";
    } else
    if(_comp == "-A" || _comp == "-M")
    {
      mask = "110011";
    } else
    if(_comp == "D+1")
    {
      mask = "011111";
    } else
    if(_comp == "A+1" || _comp == "M+1")
    {
      mask = "110111";
    } else
    if(_comp == "D-1")
    {
      mask = "001110";
    } else
    if(_comp == "A-1" || _comp == "M-1")
    {
      mask = "110010";
    } else
    if(_comp == "D+A" || _comp == "D+M" || _comp == "A+D" || _comp == "M+D")
    {
      mask = "000010";
    } else
    if(_comp == "D-A" || _comp == "D-M")
    {
      mask = "010011";
    } else
    if(_comp == "A-D" || _comp == "M-D")
    {
      mask = "000111";
    } else
    if(_comp == "D&A" || _comp == "D&M" || _comp == "A&D" || _comp == "M&D")
    {
      mask = "000000";
    } else
    if(_comp == "D|A" || _comp == "D|M" || _comp == "A|D" || _comp == "M|D")
    {
      mask = "010101";
    }

    if(_comp.find('M') != std::string::npos)
    {
      mask = "1" + mask;
    }
    else
    {
      mask = "0" + mask;
    }

    return mask;
  }

  std::string symbol(int nr)
  {
    std::string mask;
    mask += "0";

    for(int i=14; i>=0; i--)
    {
      if(nr & (1<<i))
      {
        mask += "1";
      }
      else
      {
        mask += "0";
      }
    }

    return mask;
  }

private:
};

class SymbolTable
{
public:
  void addEntry(std::string _symbol, int _address)
  {
    m_table.insert(make_pair(_symbol, _address));
  }

  void addEntry(std::string _symbol)
  {
    addEntry(_symbol, m_ram_address);
    m_ram_address++;
  }

  bool contains(std::string _symbol)
  {
    if(m_table.find(_symbol) != m_table.end())
    {
      return true;
    }
    else
    {
      return false;
    }
  }

  int getAddres(std::string _symbol)
  {
    return m_table[_symbol];
  }

  SymbolTable()
  {
    m_table.insert(std::make_pair("SP", 0));
    m_table.insert(std::make_pair("LCL", 1));
    m_table.insert(std::make_pair("ARG", 2));
    m_table.insert(std::make_pair("THIS", 3));
    m_table.insert(std::make_pair("THAT", 4));
    m_table.insert(std::make_pair("SCREEN", 16384));
    m_table.insert(std::make_pair("KBD", 24576));

    for(int i=0; i<=15; i++)
    {
      m_table.insert(std::make_pair("R" + std::to_string(i), i));
    }
  }
private:
  int m_ram_address = 16;

  std::map<std::string, int> m_table;

};

int main(int argc, char *argv[])
{
  if(argc != 2)
  {
    std::cerr<<"Usage: "<<argv[0]<<" <asm file>\n";
    exit(1);
  }

  Parser parser(argv[1]);
  Code code;
  SymbolTable table;
  std::ofstream fout("out.hack");

  while(parser.hasMoreCommands())
  {
    parser.advance();
    if(parser.commandType() == Parser::eL_COMMAND)
    {
      std::string _symbol = parser.symbol();

      if(!table.contains(_symbol))
      {
        table.addEntry(_symbol, parser.getLineNr());
      }

    }
    else if(parser.commandType() == Parser::eA_COMMAND || parser.commandType() == Parser::eC_COMMAND)
    {
      parser.increment();
    }

  }

  parser.reset();


  while(parser.hasMoreCommands())
  {
    parser.advance();
    std::string answer = "";
    //std::cout<<parser.commandType()<<'\n';

    if(parser.commandType() == Parser::eC_COMMAND)
    {
      answer += "111";

      std::string _comp = parser.comp();
      answer += code.comp(_comp);

      std::string _dest = parser.dest();
      answer += code.dest(_dest);

      std::string _jump = parser.jump();
      answer += code.jump(_jump);

      parser.increment();
      fout<<answer<<'\n';
    }
    else if(parser.commandType() == Parser::eA_COMMAND)
    {
      std::string _symbol = parser.symbol();
      //answer += "0";

      if(isdigit(_symbol[0]))
      {
        int nr = std::stoi(_symbol);

        answer += code.symbol(nr);

      }
      else
      {
        if(!table.contains(_symbol))
        {
          table.addEntry(_symbol);
        }

        int nr = table.getAddres(_symbol);

        answer += code.symbol(nr);
      }

      parser.increment();
      fout<<answer<<'\n';
    }
  }

  return 0;

}
