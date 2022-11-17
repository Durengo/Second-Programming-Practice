#pragma once

#include <json/json.h>
#include <queue>

namespace DURLIB
{
    enum RecursionMemberType
    {
        None,
        Parent,
        Child,
        ChildOfChild
    };

    static const char *RecursionMemberTypeToString(RecursionMemberType Type);

    struct RecursionsPerMember
    {
        // Current root recursion.
        //int Recursion;
        // Save the total amount of members from previous recursion.
        //int PreviousTotalMembers;
        // Look at the location of member from previous recursion.
        //int WhichMember;
        // Total amount of members in current recursion.
        int CurrentTotalMembers;
        // The previous member index;
        //int CoreMember;

        std::string MemberName;

        RecursionMemberType Type;

        RecursionsPerMember() : MemberName("Null"), Type(RecursionMemberType::None)
        //, Recursion(-1), PreviousTotalMembers(-1), WhichMember(-1), CurrentTotalMembers(-1), CoreMember(-1)
        {}
    };
    //bool ListOfMembers_CompareByLength(const RecursionsPerMember &a, const RecursionsPerMember &b);

    class JsonParse
    {
    private:
        std::string location;
        Json::Value *file;
        int depth = 0;
        Json::Value *trueDepthFile;
        Json::Reader *reader;
        Json::Writer *writer;
        //std::vector<std::string> total_members;
        //std::vector<std::tuple<int, int, std::string>> total_members;
        //std::vector<std::tuple<int, int, std::string>> member_children;

        std::vector<std::vector<RecursionsPerMember>> ListOfMembers;


    public:
        JsonParse(const std::string &location);
        ~JsonParse();

        std::string GetMemberAsString(int member, int child = -1, int childOfChild = -1);
        //std::string GetJsonValueAsString();
        void GetJsonValue();
        void JsonParse::GetJsonValueIteration(Json::Value &JsonValue, std::string &Key, int &KeyOccurrence, int &OccurrenceCounter, std::string &ReturnValue, int iteration);

        //std::vector<Json::String> GetMembers() const;
        //std::vector<std::string> GetMembers() const;

        void SearchKey(const std::string& key);

        void PrintJson(bool trueDepth = true);
        void PrintMetadata();
        //void PrintAllMembers();
    private:
        Json::Value *GetFile(bool trueDepth = true) const;

        Json::Value *JsonParseFile(const std::string &location);
        bool FileIsNullptr();
        void ProbeDepth(Json::Value *root);
        void GenerateTrueDepthFile();
        void GenerateMetadata();
        void IterateMetadata(std::vector<RecursionsPerMember> &itemsVector, Json::Value& iterationFile, int count);
        void ParseMetadata();
        void AssignTypes();
        //void InstantiateTypes();

        

        // DEPRECATED:
        // void ProbeMemberDepth(Json::Value *root);
        // void ProbeMemberChildren(Json::Value *root);
        // void ProbeDepthAndMembers(Json::Value *root);
    };
}