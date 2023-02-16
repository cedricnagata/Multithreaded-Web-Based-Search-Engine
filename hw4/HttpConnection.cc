/*
 * Copyright ©2022 Hal Perkins.  All rights reserved.  Permission is
 * hereby granted to students registered for University of Washington
 * CSE 333 for use solely during Fall Quarter 2022 for purposes of
 * the course.  No other use, copying, distribution, or modification
 * is permitted without prior written consent. Copyrights for
 * third-party components of this work must be honored.  Instructors
 * interested in reusing these course materials should contact the
 * author.
 */

#include <stdint.h>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <map>
#include <string>
#include <vector>

#include "./HttpRequest.h"
#include "./HttpUtils.h"
#include "./HttpConnection.h"

using std::map;
using std::string;
using std::vector;

namespace hw4 {

static const char* kHeaderEnd = "\r\n\r\n";
static const int kHeaderEndLen = 4;

bool HttpConnection::GetNextRequest(HttpRequest* const request) {
  // Use WrappedRead from HttpUtils.cc to read bytes from the files into
  // private buffer_ variable. Keep reading until:
  // 1. The connection drops
  // 2. You see a "\r\n\r\n" indicating the end of the request header.
  //
  // Hint: Try and read in a large amount of bytes each time you call
  // WrappedRead.
  //
  // After reading complete request header, use ParseRequest() to parse into
  // an HttpRequest and save to the output parameter request.
  //
  // Important note: Clients may send back-to-back requests on the same socket.
  // This means WrappedRead may also end up reading more than one request.
  // Make sure to save anything you read after "\r\n\r\n" in buffer_ for the
  // next time the caller invokes GetNextRequest()!

  // STEP 1:

  // if buffer_ doesn't include end of header
  if (buffer_.find(kHeaderEnd) == string::npos) {
    unsigned char buf[1024]; // buf to read from client

    while (1) {
      int bytes_read = WrappedRead(fd_, buf, 1024); // read from files

      if (bytes_read == -1) {
        return false;
      } else if (bytes_read == 0) { // end of file
        break;
      } else  {
        // add bytes read to buffer
        buffer_ += std::string(reinterpret_cast<char *>(buf), bytes_read);

        // see if buffer includes header end
        if (buffer_.find(kHeaderEnd) != string::npos) {
          break;
        }

        continue; // if header end not included continue reading
      }
    }
  }

  // find end position
  size_t end_pos = buffer_.find(kHeaderEnd);
  if (end_pos == string::npos) {
    return false;
  }

  std::string req_str = buffer_.substr(0, end_pos); // create request
  *request = ParseRequest(req_str); // parse request

  buffer_.erase(0, end_pos + kHeaderEndLen); // erase buffer

  return true;
}

bool HttpConnection::WriteResponse(const HttpResponse& response) const {
  string str = response.GenerateResponseString();
  int res = WrappedWrite(fd_,
                         reinterpret_cast<const unsigned char*>(str.c_str()),
                         str.length());
  if (res != static_cast<int>(str.length()))
    return false;
  return true;
}

HttpRequest HttpConnection::ParseRequest(const string& request) const {
  HttpRequest req("/");  // by default, get "/".

  // Plan for STEP 2:
  // 1. Split the request into different lines (split on "\r\n").
  // 2. Extract the URI from the first line and store it in req.URI.
  // 3. For the rest of the lines in the request, track the header name and
  //    value and store them in req.headers_ (e.g. HttpRequest::AddHeader).
  //
  // Hint: Take a look at HttpRequest.h for details about the HTTP header
  // format that you need to parse.
  //
  // You'll probably want to look up boost functions for:
  // - Splitting a string into lines on a "\r\n" delimiter
  // - Trimming whitespace from the end of a string
  // - Converting a string to lowercase.
  //
  // Note: If a header is malformed, skip that line.

  // STEP 2:

  // vectors for lines and first line splits
  std::vector<string> lines;
  std::vector<string> first;

  // split into lines
  boost::algorithm::split(lines, request, boost::is_any_of("\r\n"), boost::algorithm::token_compress_on);

  // trim spaces for each line
  for (std::string line : lines) {
    boost::trim(line);
  }

  // split first line to tokens
  boost::algorithm::split(first, lines[0], boost::is_any_of(" "), boost::algorithm::token_compress_on);

  req.set_uri(first[1]); // set uri from first line

  lines.erase(lines.begin()); // erase first line

  // iterate through remaining lines
  for (std::string curr_line : lines) {
    std::vector<string> full_header; // get full header for each line
    std::string header_name;
    std::string header_val;

    // split header by ': '
    boost::algorithm::split(full_header, curr_line, boost::is_any_of(": "), boost::algorithm::token_compress_on);

    // assign lowercase header name and val
    header_name = full_header[0];
    boost::algorithm::to_lower(header_name);
    header_val = full_header[1];

    req.AddHeader(header_name, header_val); // add header to request
  }

  return req;
}

}  // namespace hw4
