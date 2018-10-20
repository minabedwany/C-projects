#include "String.h" 

String ::  String( const char * s)
    : buf(strdup(s))
{
}

String :: String( const String & s )
    : buf(strdup(s.buf))
{
}

String & String :: operator = ( const String & s )
{
    if (strlen(buf)!= strlen(s.buf))
        resizeTo(strlen(s.buf));
    delete_char_array(buf);
    buf = strdup(s.buf);
    return *this;
}

char & String :: operator [] ( int index )
{
    if(inBounds(index))
        return buf[index];
    cerr << "Out of bound ";
    return buf[0];
}
int String :: size()
{
    return strlen(buf);
}

String String :: reverse()    // does not modify this String
{
char * result = new_char_array(strlen(buf) + 1);
reverse_cpy(result,buf);
String ret(result);
delete_char_array(result);
return ret;
}

int String :: indexOf( const char c )
{   
   char * p = strchr(buf, c);
    if (p){
        return p - buf;
    }
    cerr<<"Not found in string! ";
    return -1;
}

int String :: indexOf( const String pattern )
{
    char * p = strstr(buf, pattern.buf);
    if (p)
        return  p - buf;
    cerr<<"Not found in String! ";
    return -1;
}

bool String :: operator == ( const String s )
{
    return strcmp(buf, s.buf) == 0;
}

bool String :: operator != ( const String s )
{
    return strcmp(buf, s.buf) != 0;
}

bool String :: operator > ( const String s )
{
    return strcmp(buf, s.buf) > 0;
}

bool String :: operator < ( const String s )
{
    return strcmp(buf, s.buf) < 0;
}

bool String :: operator <= ( const String s )
{
    return strcmp(buf, s.buf) <=  0;
}

bool String :: operator >= ( const String s )
{
    return strcmp(buf, s.buf) >=  0;
}

        /// concatenates this and s to return result
String String :: operator + ( const String s )
{   
    char * p = new_char_array(strlen(buf) + strlen(s.buf)+1);
    strcpy(p, buf); 
    strcat(p, s.buf);
    String ret(p);
    delete_char_array(p);
    return ret;

}

        /// concatenates s onto end of this string
String String :: operator += ( const String s )
{   
    char * p =  new_char_array(strlen(buf) + strlen(s.buf)+1);
    strcpy(p, buf);
    strcat(p, s.buf);
    delete_char_array(buf);  
    buf = p;
    String ret(buf);
    return ret;
}

void String :: print( ostream & out )
{
    for (int i = 0; buf[i]!= '\0'; ++i)
        out << buf[i];
}

void String :: read( istream & in )
{
    char a[256];
    in.getline(a, 256);
    delete_char_array(buf);
    buf = strdup(a);
}

String :: ~String()
{
    delete_char_array(buf);
}

void String :: final_report_on_allocations()
{   
    cout << "Number of new allocations minus number of delete deallocations is " 
    <<num_allocations<<endl;
    if (num_allocations > 0) 
        error("Memory Leak in class String");
    if (num_allocations < 0) 
        error("Too many delete[]s in class String");
    if (num_allocations == 0)
        cout << "Allocations & deallocations match\n";
       
}

char * String :: new_char_array(int n_bytes)
{
    ++num_allocations;
    return new char[n_bytes];
}

void String :: delete_char_array(char * p)
{
    --num_allocations;
    if (num_allocations < 0) error("more delete[] than new[]");
        delete [] p;
}

void String :: error(const char * p)
{
    cerr<< "Error (class String): "<<p<<endl;
}

bool String :: inBounds( int i )
{
    return i >= 0 && i < strlen(buf);
}

int String :: num_allocations = 0; 

void String :: resizeTo(int newSize)
{
    delete_char_array(buf);
    buf = new_char_array(newSize);
}       

int String ::  strlen( const char *s )
{
    int len = 0;
    for (int i = 0; s[i] != '\0'; ++i)
        ++len;
    return len;
}

char * String :: strdup(const char *src)
{
    return strcpy(new_char_array(strlen(src) + 1), src);
}

char * String :: strcpy( char *dest, const char *src )
{    
    int i;
    for (i = 0; src[i] != '\0'; ++i)
        dest[i] = src[i];
    dest[i] = '\0';
    return dest;
}

char * String :: strcat(char *dest, const char *src)
{
    strcpy(dest + strlen(dest), src);
    return dest;
}

int String :: strcmp( const char *left, const char *right )
{
    for (int i = 0; left[i] != '\0' || right[i] != '\0'; ++i)
        if (left[i] != right[i])
            return left[i] - right[i];
    return 0;
}

int String :: strncmp( const char *left, const char *right, int n )
{
    for (int i = 0; i<n; ++i)
        if (left[i] != right[i])
            return left[i] - right[i];
    return 0;
}

char * String :: strchr( char *str, int c )
{
    for (int i= 0; str[i] != '\0'; ++i)
    {  
        if (str[i] == (char)c)
            return str+i;  //str +i is same as &(str[i])
    }                      //and str[i] is same as *(str +i)
    return nullptr;
}

        /* haystack “The quick brown fox ran up the lazy log”
           needle “ran” */
const char * String :: strstr( const char *haystack, const char *needle )
{
    return const_cast<const char *>(strstr(const_cast<char *>(haystack),
    const_cast<char *>(needle)));
}

char * String :: strstr( char *haystack, const char *needle )
{
    int len = strlen(needle);
    char * s = haystack;
    char * p;
    while(*s != '\0')
    {
        p = strchr(s, needle[0]);
        if (p == nullptr)
            return nullptr;
        if (strncmp(p, needle, len) == 0)
            return p;
        else
            s = p + 1;
        }
    return nullptr;
}

void String :: reverse_cpy( char *dest, const char *src )
{
    int len = strlen(src);
    for (int i = len-1; i>=0; --i)
        dest[len -i -1] = src[i];
    dest[len] = '\0';
}


ostream & operator << ( ostream & out, String  str )
{
    str.print(out);
    return out;
}

istream & operator >> ( istream & in, String & str )
{
    str.read(in);
    return in;
}
          
