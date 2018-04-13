#include <iostream>
#include <string>
#include <map>

// Stuff for AJAX
#include "cgicc/Cgicc.h"
#include "cgicc/HTTPHTMLHeader.h"
#include "cgicc/HTMLClasses.h"

#include "PhoneBook.h"
#include "PhoneEntry.h"

#define XML_USE_STL

using namespace std;
using namespace cgicc; // Needed for AJAX functions.

int main() {
  Cgicc cgi;    // Ajax object
  char *cstr;
  ofstream logfile;
  logfile.open("/tmp/shurbertphone.txt",ios::out | ios::app);
  if (logfile.is_open()) {
  	logfile << "Hello Jensen!!!" << endl;
  } else {
  cout << "File fail!!" << endl;
  }
  logfile.close();
  
  
  PhoneBook pb; // Phone Book SQL Interface Object
  vector<PhoneEntry> pbResults;
  
  // Create AJAX objects to recieve information from web page.
  form_iterator op = cgi.getElement("operation");
  form_iterator searchString = cgi.getElement("find");
  form_iterator addFirst = cgi.getElement("addFirst");
  form_iterator addLast = cgi.getElement("addLast");
  form_iterator addPhone = cgi.getElement("addPhone");
  form_iterator addType = cgi.getElement("addType");
  form_iterator editFirst = cgi.getElement("editFirst");
  form_iterator editLast = cgi.getElement("editLast");
  form_iterator editPhone = cgi.getElement("editPhone");
  form_iterator editType = cgi.getElement("editType");
  form_iterator editID = cgi.getElement("editID");
  form_iterator deleteID = cgi.getElement("deleteID");

  string operation = **op;
  
  string search = **searchString;
    string addfirstname = **addFirst;
  string addlastname = **addLast;
  string addphonenum = **addPhone;
  string addtypename = **addType;
  string editfirstname = **editFirst;
  string editlastname = **editLast;
  string editphonenum = **editPhone;
  string edittypename = **editType;
  string editid = **editID;
  string deleteid = **deleteID;
  
  //Used for testing 
  logfile.open("/tmp/shurbert/phone.txt",ios::out | ios::app);
  logfile << addfirstname << endl;
  logfile.close();


  string output = " ";
  if (operation == "Find Last") {
    pbResults = pb.findByLast(search);
    if (pbResults.size() > 0) {
      output = "success";
      for (int i = 0; i<pbResults.size(); i++) {
	output += "," + pbResults.at(i).first + ","
	  + pbResults.at(i).last + ","
	  + pbResults.at(i).phone + ","
	  + pbResults.at(i).type + ","
	  + pbResults.at(i).recnum;

      }
    } else {
      output = "No Match Found";
    }
  } else if (operation == "Find First") {
  pbResults = pb.findByFirst(search);
    if (pbResults.size() > 0) {
      output = "success";
      for (int i =0; i < pbResults.size(); i++) {
        output += "," + pbResults.at(i).first + ","
          + pbResults.at(i).last + ","
          + pbResults.at(i).phone + ","
          + pbResults.at(i).type + ","
          + pbResults.at(i).recnum;
      }
  } else {
      output = "No match found";
  }
} else if (operation == "Find Type") {
    pbResults = pb.findByType(search);
    if (pbResults.size() > 0) {
      output = "success";
      for (int i =0; i < pbResults.size(); i++) {
        output += "," + pbResults.at(i).first + ","
          + pbResults.at(i).last + ","
          + pbResults.at(i).phone + ","
          + pbResults.at(i).type + ","
          + pbResults.at(i).recnum;
      }
    }
    } else if (operation == "Add Entry") {
    pb.addEntry(addfirstname, addlastname, addphonenum, addtypename);
    output += "Added Entry";
  } else if (operation == "Edit Entry") {
    pb.editEntry(editfirstname, editlastname, editphonenum, edittypename, editid);
    output += "Edited Entry";
  } else if (operation == "Delete Entry") {
    pb.deleteEntry(deleteid);
    output += "Deleted Entry";
  } else {
    output = "No Match Found";
  }
  
  
  /* send back the results */
  cout << "Content-Type: text/plain\n\n";
  cout << output << endl;
  
  
  return 0;
}

