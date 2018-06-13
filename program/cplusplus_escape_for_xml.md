[cpp.sh](http://cpp.sh/)<br>

```
// Example program
#include <iostream>
#include <string>

static char to_hex(unsigned char c, char e = '-') 
{ 
	if(c < 10) return (char)(c + '0');
	else if(c <= 0x0f) return (char)(c - 10 + 'A');
	return e; 
}

int
urlprint(const std::string& in, std::string& out)
{
	size_t len = in.length();
	out.clear();
	out.reserve(len * 3);

	size_t i = 0;
	while (i < len)
	{
		if ((in[i]) >= 0x20 && (in[i]) <= 0x7e)
		{
			out += in[ i ];
		}
		else
		{
			char tmp[4];
			tmp[0] = '%';
			tmp[1] = to_hex(((unsigned char)(in[i] & 0xf0)) >> 4);
			tmp[2] = to_hex((unsigned char)(in[i] & 0x0f));
			tmp[3] = '\0';
			out += tmp;
		}
		++i;
	}

	return out.length();
}

void
escape(std::string *data)
{
    std::string::size_type pos = 0;
    for (;;)
    {
        pos = data->find_first_of("\"&<>", pos);
        if (pos == std::string::npos) break;
        std::string replacement;
        switch ((*data)[pos])
        {
        case '\"': replacement = "&quot;"; break;   
        case '&':  replacement = "&amp;";  break;   
        case '<':  replacement = "&lt;";   break;   
        case '>':  replacement = "&gt;";   break;   
        default: ;
        }
        data->replace(pos, 1, replacement);
        pos += replacement.size();
    };
}

void
escape2(std::string& data) {
    std::string buffer;
    buffer.reserve(data.size());
    for(size_t pos = 0; pos != data.size(); ++pos) {
        switch(data[pos]) {
            case '&':  buffer.append("&amp;");       break;
            case '\"': buffer.append("&quot;");      break;
            case '\'': buffer.append("&apos;");      break;
            case '<':  buffer.append("&lt;");        break;
            case '>':  buffer.append("&gt;");        break;
            default:   buffer.append(&data[pos], 1); break;
        }
    }
    data.swap(buffer);
}

int main()
{
  std::string name;
  std::cout << "What is your name? ";
  getline (std::cin, name);
  std::cout << "Hello, " << name << "!\n";
  
  std::string in = "/ad/g/1?nw=188286&amp;resp=ad&csid=pixel1";
  std::string out;
  urlprint(in, out);
  escape(&out);
  escape2(out);
  std::cout << out << std::endl;
}
```
