#include "CppUnitTest.h"
#include <filesystem>

#include "../MiniSysAssembler/pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test {
TEST_CLASS(doAssemble){
	private:
		bool isSameFile(std::string path1, std::string path2) {
			std::fstream file1, file2;
			file1.open(path1);
			file2.open(path2);
			Assert::IsTrue(file1.is_open());
			Assert::IsTrue(file2.is_open());
			while (!file1.eof()) {
	        	   std::string line1, line2;
				   getline(file1, line1);
				   getline(file2, line2);
                   if (line1 != line2) return false;
	        }
			return true;
		}

    public:
        TEST_METHOD(doAssemble_Test){
            std::string out_path = std::filesystem::temp_directory_path().string();
            Assert::IsFalse(
                ::doAssemble("../../Test/TestData/test.asm", out_path));
            Assert::IsTrue(
                isSameFile(out_path + "dmem32.coe",
                           "../../Test/TestData/CorrectAnswer/dmem32.coe"));
            Assert::IsTrue(
                isSameFile(out_path + "prgmip32.coe",
                           "../../Test/TestData/CorrectAnswer/prgmip32.coe"));
            std::filesystem::remove(out_path + "dmem32.coe");
            std::filesystem::remove(out_path + "prgmip32.coe");
        }

};
}