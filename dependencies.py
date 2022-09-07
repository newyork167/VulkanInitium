import platform

requires = (
    ("assimp/5.0.1"),
    ("fmt/9.0.0"),
    ("bullet3/3.24"),
    ("glew/2.1.0"),
    ("glad/0.1.34"),
    ("glfw/3.3.6"),
    ("glm/0.9.9.8"),
    ("stb/20200203"),
    ("imgui/1.79"),
    ("spdlog/1.10.0"),
    ("boost/1.79.0"),
)

if platform.system() in ["Darwin"]:
    requires = requires + (("moltenvk/1.1.10"),)

options = '''
  glew:shared=False
'''