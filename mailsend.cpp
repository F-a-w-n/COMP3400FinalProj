// mailsend.cpp - original code by Fawn Barisic - sends an email to a customer to notiy of an unpaid bill
#define CURL_STATICLIB
#include "./curl/curl.h"
#include <string>
#include <iostream>

using namespace std;

class MailSend {
  public:
  
  static bool send_email_with_attachment(string recipient,
                                        string subject,
                                        string body,
                                        string attachment_path) {

    // values consistent across all emails
    const string smtp_server = "smtp://smtp.gmail.com:587"; // gmail smtp server which we send the information to
    const string from = "pcklrchrd@gmail.com";              // spare personal email for testing, very professional
    const string username = "pcklrchrd@gmail.com";          // email is the username to login
    const string password = "oktjaifddljkiisx";             // custom password for this use case
    CURL *curl = curl_easy_init(); // initializes curl library
    CURLcode res = CURLE_OK; // error code from libcurl, defaults to OK
    FILE *attachment_file = NULL; // the attachment will be stored here once opened
    struct curl_slist *recipients = NULL; //stores a list of recipients to send to, in our case we only use one
    
    cout << "Sending email..." << endl;

    // initialization error
    if (!curl) {
      cerr << "Failed to initialize libcurl" << endl;
      return false;
    }
    
    // Opens the attached file
    attachment_file = fopen(attachment_path.c_str(), "rb");
    if (!attachment_file) {
      cerr << "Failed to open attachment file: " << attachment_path << endl;
      curl_easy_cleanup(curl); // closes the curl
      return false;
    }
    
    // Sets up the email's headers, body, and attachment
    string email_headers = "From: " + from + "\r\n"
                      "To: " + recipient + "\r\n"
                      "Subject: " + subject + "\r\n"
                      "MIME-Version: 1.0\r\n"
                      "Content-Type: multipart/mixed; boundary=\"BOUNDARY123\"\r\n"
                      "\r\n"
                      "--BOUNDARY123\r\n"
                      "Content-Type: text/plain; charset=utf-8\r\n"
                      "Content-Transfer-Encoding: 7bit\r\n"
                      "\r\n"
                      + body + "\r\n"
                      "\r\n"
                      "--BOUNDARY123\r\n"
                      "Content-Type: application/octet-stream; name=\"" + 
                      attachment_path.substr(attachment_path.find_last_of("/\\") + 1) + "\"\r\n"
                      "Content-Transfer-Encoding: base64\r\n"
                      "Content-Disposition: attachment; filename=\"" + 
                      attachment_path.substr(attachment_path.find_last_of("/\\") + 1) + "\"\r\n"
                      "\r\n";
    
    // Sets up the email footer
    string email_footer = "\r\n--BOUNDARY123--\r\n\r\n.\r\n";
    
    // Calculates the total size (headers + file + footer)
    fseek(attachment_file, 0, SEEK_END);
    long file_size = ftell(attachment_file);
    fseek(attachment_file, 0, SEEK_SET);
    long total_size = email_headers.size() + ((file_size+2)/3)*4 + ((file_size+53)/54)*2 + email_footer.size() - 2; // calculation complicated by conversion of the file to base64 to be emailed
    
    // struct to store the current state of uploading the email
    struct UploadContext {
      const string* headers;
      const string* footer;
      FILE* file;
      size_t headers_sent;
      size_t file_size;
      size_t file_sent;
      string pending_data;
      size_t footer_sent;
    } context = {       // initializes an empty context to start
      &email_headers, 
      &email_footer, 
      attachment_file, 
      0,
      static_cast<size_t>(file_size),
      0,
      "",
      0
    };

    // Set libcurl options
    curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE, (curl_off_t)total_size);
    curl_easy_setopt(curl, CURLOPT_URL, smtp_server.c_str());
    curl_easy_setopt(curl, CURLOPT_MAIL_FROM, from.c_str());
    
    recipients = curl_slist_append(recipients, recipient.c_str());
    curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);
    
    curl_easy_setopt(curl, CURLOPT_USERNAME, username.c_str());
    curl_easy_setopt(curl, CURLOPT_PASSWORD, password.c_str());
    curl_easy_setopt(curl, CURLOPT_USE_SSL, (long)CURLUSESSL_ALL); // uses SSL encryption
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30L);                  // 30s timeout to ensure enough time to connect
    curl_easy_setopt(curl, CURLOPT_TIMEOUT_MS, 60000L);            // 60s timeout to ensure enough time to send

    curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_callback);  // passes the callback function defined below to read the email data to a buffer
    curl_easy_setopt(curl, CURLOPT_READDATA, &context);
    curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);                   // file upload
    
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L);
    curl_easy_setopt(curl, CURLOPT_CAINFO, "cacert.pem"); // ca cert to ensure secure connection
    
    res = curl_easy_perform(curl); // sends the email
    
    // frees all used data
    if (attachment_file)
      fclose(attachment_file);
    if (recipients)
      curl_slist_free_all(recipients);
    curl_easy_cleanup(curl);
    
    if (res != CURLE_OK) {
      cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
      return false;
    }
    
    cout << "Email sent successfully!" << endl;
    return true;
  }
  
  
  // base64 conversion for file attachments to comply with smtp
  static string base64(const unsigned char* bytes_to_encode, size_t byte_count) {
    static const string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"; // all base64 characters
    string ret; //encoded string
    int i = 0; // index in char_array_3
    int j = 0; //index in char_array_4
    unsigned char char_array_3[3]; //
    unsigned char char_array_4[4];

    // converts each character to base64, uses bitwise & to divide a base 256 char to base 64 chars
    while (byte_count--) {
        char_array_3[i++] = *(bytes_to_encode++);
        if (i == 3) {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;

            for(i = 0; (i <4) ; i++) // adds the encoded chars to the return string
                ret += base64_chars[char_array_4[i]];
            i = 0;
        }
    }
    // continues the conversion at the end of a string where (length % 3) != 0
    if (i) {
        for(j = i; j < 3; j++) // empties char_array_3 as there is no more data to encode
            char_array_3[j] = '\0';

        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
        char_array_4[3] = char_array_3[2] & 0x3f;

        for (j = 0; (j < i + 1); j++) // only adds the remaining chars to avoid reusing garbage data
            ret += base64_chars[char_array_4[j]];

        while((i++ < 3))
            ret += '=';
    }

    return ret;
  }

  // callback function to read email data into the curl buffer
  static size_t read_callback(void *outbuf, size_t size, size_t members, void *ctxt) {
    struct UploadContext {
        const string* headers;
        const string* footer;
        FILE* file;
        size_t headers_sent;
        size_t file_size;
        size_t file_sent;
        string pending_data;
        size_t footer_sent;
    } *context = (struct UploadContext *)ctxt; // takes the current context
    size_t bytes_to_copy = 0;
    
    // Sends headers first, stops when no more data to send
    if (context->headers_sent < context->headers->size()) {
        size_t remaining = context->headers->size() - context->headers_sent;
        bytes_to_copy = min(size * members, remaining);                                   // chooses the size of the buffer unless the data to send is less than the size of the buffer
        memcpy(outbuf, context->headers->c_str() + context->headers_sent, bytes_to_copy); // copies data to the buffer
        context->headers_sent += bytes_to_copy; // updates sent amount
        return bytes_to_copy; // returns amount copied
    }
    
    // Sends attachment next, stops at the end of the file
    if (context->file && context->file_sent < context->file_size) {
        const size_t BUF_SIZE = 54; // 54 raw bytes becomes exactly 72 Base64 chars, easier to work with
        unsigned char buffer[BUF_SIZE];
        
        size_t remaining_bytes = context->file_size - context->file_sent;
        size_t bytes_to_read = min(BUF_SIZE, remaining_bytes);           // chooses the buffer size unless there is less data than the size of the buffer

        if (bytes_to_read > 0) {
            size_t bytes_read = fread(buffer, 1, bytes_to_read, context->file);  // reads data from file
            if (bytes_read > 0) {
                string encoded = base64(buffer, bytes_read);   // if the read is successful, converts to base64
                if (context->file_sent > 0 && context->file_sent % BUF_SIZE == 0) {  // every 54 characters adds a newline
                    encoded = "\r\n" + encoded;
                }
                bytes_to_copy = min(size * members, encoded.size()); // copies the max amount by curl or the size of the encoded string, whichever is smallest
                memcpy(outbuf, encoded.c_str(), bytes_to_copy);
                
                if (bytes_to_copy < encoded.size()) { // stores the remaining read data for later
                    context->pending_data = encoded.substr(bytes_to_copy);
                }
                context->file_sent += bytes_read; // updates the context and returns data size
                return bytes_to_copy;
            }
        }
    }
    
    // Sends any pending Base64 data
    if (!context->pending_data.empty()) {
        bytes_to_copy = min(size * members, context->pending_data.size());
        memcpy(outbuf, context->pending_data.c_str(), bytes_to_copy);
        context->pending_data.erase(0, bytes_to_copy);
        return bytes_to_copy;
    }
    
    // Finally sends footer if not sent yet
    if (context->file_sent >= context->file_size && 
        context->pending_data.empty() &&
        context->footer_sent < context->footer->size()) {
      size_t remaining = context->footer->size() - context->footer_sent;
      bytes_to_copy = min(size * members, remaining);
      memcpy(outbuf, context->footer->c_str() + context->footer_sent, bytes_to_copy); // copies full buffer or remaining amount of string
      context->footer_sent += bytes_to_copy; // updates context and returns sent bytes
      return bytes_to_copy;
    }
    
    if (context->headers_sent >= context->headers->size() &&
        context->file_sent >= context->file_size &&
        context->pending_data.empty() &&
        context->footer_sent >= context->footer->size()) { // only returns 0 when all data is sent
      return 0;
    }
    return size * members;
  }
};

/*
  int main()
  {
    // Example usage
    string to = "barisicc@uwindsor.ca";
    string subject = "Test email with attachment";
    string body = "Hello,\n\nWe are sending you this email to remind you of your due electrical bill. Please review the attached bill and send payment at your earliest convenience.\n\nBest regards,\nThe PowerPlex Team";
    string attachment_path = "./ExpenseReport.txt";
    
    bool success = MailSend::send_email_with_attachment(to, subject, body, attachment_path);
    
    return 0;
}
*/