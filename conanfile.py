from conans import ConanFile, CMake, tools


class FspEvalConan(ConanFile):
    name = "fsp-eval"
    version = "0.1"
    license = "<Put the package license here>"
    author = "<Put your name here> <And your email here>"
    url = "<Package recipe repository url here, for issues about the package>"
    description = "Flowshop evaluation methods"
    topics = ("flowshop", "permutation", "optimization")
    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake"
    exports_sources = "src/*", "cmake/*", "CMakeLists.txt", "test/*"

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

    def build(self):

        line_to_replace = 'include(cmake/StandardProjectSettings.cmake)'
        tools.replace_in_file("CMakeLists.txt", line_to_replace,
                              '''{}
include("{}/conanbuildinfo.cmake")
conan_basic_setup()'''.format(line_to_replace, self.install_folder.replace("\\", "/")))

        cmake = CMake(self)
        cmake.definitions["ENABLE_TESTING"] = "OFF"
        cmake.configure(source_folder=".")
        cmake.build()
        
    def package(self):
        self.copy("*.h", dst="include", src="src")

    def package_info(self):
        self.cpp_info.libs = ["fsp-eval"]

