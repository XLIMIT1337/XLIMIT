#include <httplib.h>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <filesystem>

int main() {
    httplib::Server svr;

    std::string htmlContent = "<!DOCTYPE html><html lang='en'><head><title>XLIMIT</title><style>body{margin:0;padding:0;background-color:#f2f2f2;font-family:Arial;color:#333;}#container{max-width:900px;margin:50px auto;background-color:#f0f0f0;border:1px solid #a9a9a9;}#title-container{padding:8px 10px;background-color:#e2e2e2;border:1px solid #a9a9a9;}#title{font-size:14px;font-weight:bold;color:#333;}#file-container{padding:8px 10px;border:1px solid #a9a9a9;background-color:#fff;font-size:12px;}#file-name{display:inline-block;}#file-container a{float:right;color:#ff6600;text-decoration:none;font-size:12px;font-weight:bold;}#file-container a:hover{text-decoration:underline;}</style></head><body><div id='container'><div id='title-container'><div id='title'>XLIMIT</div></div>";

    for (const auto& entry : std::filesystem::directory_iterator(".")) {
        if (entry.is_regular_file()) {
            std::string fileName = entry.path().filename().string();
            htmlContent += "<div id='file-container'><div id='file-name'>" + fileName + "</div><a href='/" + fileName + "' download>DOWNLOAD</a></div>";
        }
    }

    htmlContent += "</div></body></html>";

    svr.Get("/", [&htmlContent](const httplib::Request& req, httplib::Response& res) {
        res.set_content(htmlContent, "text/html");
    });

    svr.Get(R"(/(.*))", [](const httplib::Request& req, httplib::Response& res) {
        std::string filePath = "." + req.path;
        std::ifstream file(filePath, std::ios::binary);
        if (file) {
            std::ostringstream oss;
            oss << file.rdbuf();
            res.set_content(oss.str(), "application/octet-stream");
        } else {
            res.status = 404;
            res.set_content("File Not Found", "text/plain");
        }
    });

    std::cout << "XLIMIT listening on Port 3434" << std::endl;
    svr.listen("0.0.0.0", 3434);

    return 0;
}
