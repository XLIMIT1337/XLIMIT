#include <httplib.h>
#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

int main() {
    httplib::Server svr;

    svr.Get("/", [](const httplib::Request& req, httplib::Response& res) {
        std::string htmlContent = "<!DOCTYPE html><html lang='en'><head><title>XLIMIT</title><style>body{margin:0;padding:0;background-color:#f2f2f2;font-family:Arial;color:#333;}#container{max-width:900px;margin:50px auto;background-color:#f0f0f0;border:1px solid #a9a9a9;}#title-container{padding:8px 10px;background-color:#e2e2e2;border:1px solid #a9a9a9;}#title{font-size:14px;font-weight:bold;color:#333;}#file-container{padding:8px 10px;border:1px solid #a9a9a9;background-color:#fff;font-size:12px;}#file-name{display:inline-block;}#file-container a{float:right;color:#ff6600;text-decoration:none;font-size:12px;font-weight:bold;}#file-container a:hover{text-decoration:underline;}</style></head><body><div id='container'><div id='title-container'><div id='title'>XLIMIT</div></div>";

        for (const auto& entry : fs::directory_iterator(".")) {
            if (fs::is_regular_file(entry.path())) {
                std::string fileName = entry.path().filename().string();
                htmlContent += "<div id='file-container'><div id='file-name'>" + fileName + "</div><a href='/" + fileName + "' download>DOWNLOAD</a></div>";
            }
        }

        htmlContent += "</div></body></html>";
        res.set_content(htmlContent, "text/html");
    });

    svr.Get(R"(/(.*))", [](const httplib::Request& req, httplib::Response& res) {
        std::string filePath = "." + req.path;
        if (fs::exists(filePath) && fs::is_regular_file(filePath)) {
            std::ifstream file(filePath, std::ios::binary);
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
