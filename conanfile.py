from conans import ConanFile, CMake, tools


class FspEvalConan(ConanFile):
    name = "fsp-eval"
    version = "0.1"
    license = "LICENCE"
    author = "Lucas Marcondes Pavelski <lpavelski@alunos.utfpr.edu.br>"
    url = ""
    description = "Flowshop evaluation methods"
    topics = ("flowshop", "permutation", "optimization")
    
    # No settings/options are necessary, this is header only
    exports_sources = "src/*"
    no_copy_source = True

    def build(self):
        pass

    def package(self):
        self.copy("*.hpp", dst="include", src="src")

    def package_id(self):
        self.info.header_only()

    def package_info(self):
        self.cpp_info.name = "fsp-eval"
        self.cpp_info.includedirs = ['include']
