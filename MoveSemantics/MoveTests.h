#include <string>

struct MoveTest1
{
   MoveTest1              ();
   MoveTest1              (const char* name);
   ~MoveTest1             ();

   MoveTest1              (const MoveTest1&);
   MoveTest1              (MoveTest1&&);

   MoveTest1&  operator = (const MoveTest1&);
   MoveTest1&  operator = (MoveTest1&&);

   const char* getName    () const;

   void        printName  () const;

private:

   std::string m_name;
   char*       m_singleChar;
};
