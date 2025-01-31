Here's the complete README.md ready for copying:

```markdown
# Locker - Secure CLI Password Manager 🔒

![Security](https://img.shields.io/badge/Security-Level_3_Critical-red)
![Build](https://img.shields.io/badge/Build-In_Development-yellow)
![License](https://img.shields.io/badge/License-MIT-green)

A security-focused command-line password manager with multiple encryption schemes and secure memory handling.

## Features 
- **8 Encryption Schemes** with credential-derived keys
- Secure memory zeroization 
- JSON data handling with libjson
- OpenSSL-powered cryptography (libssl)
- CLI-only operation 
- Backup/restore functionality
- Secure password generator

## Installation ⚙️
```bash
git clone https://github.com/yourusername/Locker.git
cd Locker
sudo apt-get install libssl-dev libjson-c-dev  # Debian/Ubuntu
make
```

## Usage 
```bash
# Initialize new user
./Locker -i

# Add account (interactive):
./Locker -u <user> -P <pass> -n

# List accounts:
./Locker -u <user> -P <pass> -d

# Generate password:
./Locker -u <user> -P <pass> -r 16

# Delete account #2:
./Locker -u <user> -P <pass> -D 2

# Create backup:
./Locker -u <user> -P <pass> -b

# Restore backup:
./Locker -u <user> -P <pass> -R
```

## Command Reference 📖
| Option | Action                  | Arguments       |
|--------|-------------------------|-----------------|
| `-i`   | Initialize user         | None            |
| `-u`   | Username                | Required        |
| `-P`   | Master password         | Required        |
| `-n`   | Add account             | None            |
| `-d`   | List accounts           | None            |
| `-D`   | Delete account          | Account number  |
| `-b`   | Create backup           | None            |
| `-R`   | Restore backup          | None            |
| `-r`   | Generate password       | Length          |

## Security 
```mermaid
graph TD
    A[Credentials] --> B[Key Derivation]
    B --> C{Encryption}
    C --> D[AES-256-GCM]
    C --> E[ChaCha20]
    C --> F[...]
    D --> G[Encrypted JSON]
    E --> G
    F --> G
```

## Development Status 
```plaintext
███████████████████████░░ 85% 
```
- Core functionality complete
- Memory security implemented
- Testing ongoing
- Crypto audit pending

⚠️ **Warning**: Not production-ready! Use only with test credentials.

## Contributing 
1. Fork repository
2. Create feature branch
3. Submit PR with description
4. Follow secure coding guidelines

## License 📄
MIT License - See [LICENSE](LICENSE) for details
```

Just copy all content between the triple backticks (including the security diagram and status indicator) into a new file called `README.md` in your project root.
