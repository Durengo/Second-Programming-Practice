#include "JsonParse.h"

#include "durlib/Log/Log.h"
#include <algorithm>
#include <fstream>

namespace DURLIB
{
    static const char *RecursionMemberTypeToString(RecursionMemberType Type)
    {
        switch (Type)
        {
        case RecursionMemberType::None:
            return "None";
        case RecursionMemberType::Parent:
            return "Parent";
        case RecursionMemberType::Child:
            return "Child";
        case RecursionMemberType::ChildOfChild:
            return "Child of Child";
        default:
            CLI_ASSERT(0, "INVALID SHEET TYPE IN FUNCTION \"SheetTypeToString\"");
            return "";
        }
    }

    // bool ListOfMembers_CompareByLength(const RecursionsPerMember &a, const RecursionsPerMember &b)
    // {
    //     return a.Recursion < b.Recursion;
    // }

    JsonParse::JsonParse(const std::string &location)
        : location(""), file(nullptr),
          trueDepthFile(nullptr),
          reader(nullptr), writer(nullptr)
    {
        file = JsonParseFile(location);
        CLI_ASSERT(FileIsNullptr(), "JSON VALUE \"FILE\" IS NULLPTR");
        ProbeDepth(file);
        // ProbeMemberDepth(file);
        // ProbeDepthAndMembers(file);
        // ProbeMemberChildren(file);
        GenerateTrueDepthFile();
        GenerateMetadata();
        CLI_INFO("NEW JSON HAS BEEN LOADED. DEPTH SIZE = {0}", depth);
    }

    JsonParse::~JsonParse()
    {
        delete (writer);
        delete (reader);
        delete (file);
    }

    // std::vector<Json::String> JsonParse::GetMembers() const
    // {
    //     return file->getMemberNames();
    // }

    // std::vector<std::string> JsonParse::GetMembers() const
    // {
    //     return total_members;
    // }

    // std::string JsonParse::GetMemberAsString(int member, int child, int childOfChild)
    // {
    //     // std::string value;
    //     // CLI_INFO("Type = {0}", file->get(std::get<2>(total_members[member]), "ERRROR").type());
    //     try
    //     {
    //         if (child != -1 && childOfChild != -1)
    //         {
    //             return "";
    //         }
    //         if (child != -1)
    //         {
    //             CLI_INFO("member at  position {0} = {1}, child at position {2} = {3}", member, std::get<2>(total_members[member]), child, std::get<2>(member_children[child]));
    //             int childPos = (1 * std::get<1>(total_members[member])) + child;
    //             return file->get(std::get<2>(total_members[member]), "ERROR-1-2").get(std::get<2>(member_children[childPos]), "ERROR-1-2-1").asString();
    //         }
    //         else
    //         {
    //             CLI_INFO("member at  position {0} = {1}", member, std::get<2>(total_members[member]));
    //             return file->get(std::get<2>(total_members[member]), "ERROR-1").asString();
    //         }
    //     }
    //     catch (Json::Exception &i)
    //     {
    //         CLI_ERROR("{0}", i.what());
    //         return "ERROR EXCEPTION";
    //     }
    // }

    void JsonParse::GetJsonValue()
    {
        int WhichMember = 0;
        // to lower
        std::string key = "name";
        int KeyOccurrence = 3;

        Json::Value *temp = nullptr;
        std::string returnValue = "";
        int OccurrenceCounter = 0;
        try
        {
            temp = &trueDepthFile->get(trueDepthFile->getMemberNames()[WhichMember], "ERROR");
            for (int i = 0; i < temp->getMemberNames().size(); i++)
            {
                GetJsonValueIteration(*temp, key, KeyOccurrence, OccurrenceCounter, returnValue, i);
            }
            if (OccurrenceCounter != KeyOccurrence)
            {
                CLI_WARN("KEY NOT FOUND.");
                return;
            } // FAIL
            if (OccurrenceCounter == KeyOccurrence)
            {
                CLI_INFO("KEY FOUND! KEY = {0}", returnValue);
                return;
            }
            else
            {
                CLI_ERROR("ERROR");
                return;
            }
        }
        catch (Json::Exception &i)
        {
            CLI_ERROR("{0}", i.what());
        }

        // for (int i = 0; i < WhichMember;)
    }

    void JsonParse::GetJsonValueIteration(Json::Value &JsonValue, std::string &Key, int &KeyOccurrence, int &OccurrenceCounter, std::string &ReturnValue, int iteration)
    {
        if (ReturnValue != "")
        {
            return;
        }
        Json::Value temp = JsonValue;
        std::string tempString;
        try
        {
            temp = temp.get(temp.getMemberNames()[iteration], "ERROR");
            for (int i = 0; i < temp.getMemberNames().size(); i++)
            {
                try
                {
                    temp = temp.get(temp.getMemberNames()[iteration], "ERROR");
                    GetJsonValueIteration(temp, Key, KeyOccurrence, OccurrenceCounter, ReturnValue, i);
                }
                catch (Json::Exception &i)
                {
                    CLI_ERROR("{0}", i.what());
                }
                if (ReturnValue != "")
                {
                    return;
                }
                try
                {
                    tempString = temp.get(Key, "ERROR").asString();
                    if (tempString == Key)
                    {
                        if (OccurrenceCounter == KeyOccurrence)
                        {
                            ReturnValue = tempString;
                        }
                        OccurrenceCounter++;
                    }
                }
                catch (Json::Exception &i)
                {
                    CLI_ERROR("{0}", i.what());
                }
            }
        }
        catch (Json::Exception &i)
        {
            CLI_ERROR("{0}", i.what());
        }
    }

    void JsonParse::SearchKey(const std::string &key)
    {
        std::vector<std::string> foundKeys;
        int count = 0;
        for (int i = 0; i < ListOfMembers.size(); i++)
        {
            for (int j = 0; j < ListOfMembers[i].size(); j++)
            {
                count++;
                std::string current = ListOfMembers[i][j].MemberName;
                std::string tempKey = key;
                for (int i = 0; i < current.length(); i++)
                {
                    current[i] = std::tolower(current[i]);
                }
                for (int i = 0; i < tempKey.length(); i++)
                {
                    tempKey[i] = std::tolower(tempKey[i]);
                }
                size_t found = current.find(tempKey);
                if (found != std::string::npos)
                {
                    foundKeys.push_back(ListOfMembers[i][j].MemberName);
                }
            }
        }
        if (foundKeys.size() == 0)
        {
            CLI_WARN("Found no keys.");
            return;
        }
        else
        {
            for (int i = 0; i < foundKeys.size(); i++)
            {
                CLI_INFO("{0}. Found \"{1}\" in: \"{2}\"", i + 1, key, foundKeys[i]);
            }
        }
    }

    void JsonParse::PrintJson(bool trueDepth)
    {
        // CLI_TRACE("true depth = {}", trueDepth);
        if (trueDepth)
        {
            CLI_INFO("{0}", trueDepthFile->toStyledString());
        }
        else
        {
            CLI_INFO("{0}", file->toStyledString());
        }
    }
    void JsonParse::PrintMetadata()
    {
        for (int i = 0; i < ListOfMembers.size(); i++)
        {
            for (int j = 0; j < ListOfMembers[i].size(); j++)
            {
                // CLI_INFO("i={0}|j={1}", i, j);
                switch (ListOfMembers[i][j].Type)
                {
                case RecursionMemberType::Parent:
                    CLI_WARN("NAME = {0} | TYPE = {1}", ListOfMembers[i][j].MemberName, RecursionMemberTypeToString(ListOfMembers[i][j].Type));
                    CLI_WARN("TOTAL MEMBERS = {0}", ListOfMembers[i][j].CurrentTotalMembers);
                    break;
                case RecursionMemberType::Child:
                    CLI_INFO("NAME = {0} | TYPE = {1}", ListOfMembers[i][j].MemberName, RecursionMemberTypeToString(ListOfMembers[i][j].Type));
                    CLI_INFO("TOTAL MEMBERS = {0}", ListOfMembers[i][j].CurrentTotalMembers);
                    break;
                case RecursionMemberType::ChildOfChild:
                    CLI_TRACE("NAME = {0} | TYPE = {1}", ListOfMembers[i][j].MemberName, RecursionMemberTypeToString(ListOfMembers[i][j].Type));
                    CLI_TRACE("TOTAL MEMBERS = {0}", ListOfMembers[i][j].CurrentTotalMembers);
                    break;
                case RecursionMemberType::None:
                    CLI_ERROR("NAME = {0} | TYPE = {1}", ListOfMembers[i][j].MemberName, RecursionMemberTypeToString(ListOfMembers[i][j].Type));
                    CLI_ERROR("TOTAL MEMBERS = {0}", ListOfMembers[i][j].CurrentTotalMembers);
                    break;
                default:
                    CLI_ERROR("THIS MUST NOT HAPPEN.");
                    break;
                }
                // CLI_INFO("\n\t\ti={0}|j={1}\n\t\tname = {2};\n\t\t\t\ttype = {3};\t\t\ttotal members = {4}", i, j,
                //          ListOfMembers[i][j].MemberName, RecursionMemberTypeToString(ListOfMembers[i][j].Type),
                //          ListOfMembers[i][j].CurrentTotalMembers);
            }
        }
    }
    // void JsonParse::PrintAllMembers()
    // {
    //     int internal = 0;
    //     int external = 0;
    //     for (int i = 0; i < total_members.size(); i++)
    //     {
    //         CLI_ERROR("{0} [{1}] - CHILDREN = {2}", i + 1, std::get<2>(total_members[i]), std::get<1>(total_members[i]));
    //         CLI_TRACE("val 1 = {0}, val 2 = {1}", std::get<0>(total_members[i]), std::get<1>(total_members[i]));
    //         for (int j = 0 + internal; j < member_children.size(); j++)
    //         {
    //             if (std::get<1>(member_children[j]) == i)
    //             {
    //                 CLI_ERROR("{0} [{1}] - CHILD OF = [{2}]", external + 1, std::get<2>(member_children[j]), std::get<2>(total_members[i]));
    //                 CLI_TRACE("val 1 = {0}, val 2 = {1}", std::get<0>(member_children[j]), std::get<1>(member_children[j]));
    //                 internal++;
    //                 external++;
    //             }
    //             else
    //             {
    //                 external = 0;
    //                 break;
    //             }
    //         }
    //     }
    // }

    Json::Value *JsonParse::GetFile(bool trueDepth) const
    {
        if (file == nullptr)
        {
            CLI_ASSERT(0, "JSON VALUE \"FILE\" IS NULLPTR");
            return nullptr;
        }
        // if (depth == 0)
        // {
        //     return file;
        // }
        if (trueDepth)
        {
            if (trueDepthFile == nullptr)
            {
                CLI_ASSERT(0, "JSON VALUE \"TRUE_DEPTH_FILE\" IS NULLPTR");
                return nullptr;
            }
            else
            {
                return trueDepthFile;
            }
        }
        else
        {
            return file;
        }
    }

    Json::Value *JsonParse::JsonParseFile(const std::string &location)
    {
        Json::Value *root = new Json::Value;

        std::ifstream ifs;

        ifs.open(location);

        Json::CharReaderBuilder builder;

        builder["collectComments"] = true;

        JSONCPP_STRING errs;

        if (!parseFromStream(builder, ifs, root, &errs))
        {
            CLI_ERROR("ERROR PARSING JSON FILE: {0}", errs);
            CLI_ASSERT(0, "");
            return nullptr;
        }

        // CLI_INFO("\n{0}", root.toStyledString());
        return root;
    }
    bool JsonParse::FileIsNullptr()
    {
        if (file == nullptr)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    void JsonParse::ProbeDepth(Json::Value *root)
    {
        Json::Value temp = *root;
        Json::Value prev;
        std::vector<Json::String> members;
        int count = 0;
        while (true)
        {
            members = temp.getMemberNames();
            // CLI_TRACE("MEMBERS SIZE = {0}", members.size());
            if (members.size() == 1 && temp.get(members[0], "ERROR") != "ERROR")
            {
                // CLI_ERROR("{0}", members[0]);
                temp = temp.get(members[0], "ERROR");
                try
                {
                    members = temp.getMemberNames();
                    // CLI_INFO("member = {0}", members[0]);

                    // CLI_INFO("member = {0}", temp.getMemberNames()[0]);
                }
                catch (Json::Exception)
                {
                    // CLI_ERROR("MEMBER FAILED {0}", i.what());
                    //  CLI_ERROR("COUNT = {0}", count);

                    // total_members = members;
                    depth = count;
                    break;
                }
                count++;
            }
            else
            {
                // CLI_ERROR("COUNT = {0}", count);

                // total_members = members;
                depth = count;
                break;
            }
        }
    }
    void JsonParse::GenerateTrueDepthFile()
    {
        trueDepthFile = new ::Json::Value();
        trueDepthFile = file;
        std::vector<Json::String> members = trueDepthFile->getMemberNames();
        for (int i = 0; i < depth; i++)
        {
            *trueDepthFile = trueDepthFile->get(members[0], "ERROR");
            members = trueDepthFile->getMemberNames();
        }
    }
    void JsonParse::GenerateMetadata()
    {
        // CLI_ERROR("\n\n\nTEST START");
        Json::Value File = *trueDepthFile;
        int TotalCoreVectorSize = (int)File.getMemberNames().size();
        // CLI_TRACE("FILE:\n{0}", File.toStyledString());

        for (int i = 0; i < TotalCoreVectorSize; i++)
        {
            // CLI_INFO("current counter: {0}, total vec size: {1}", i, TotalCoreVectorSize);
            std::vector<RecursionsPerMember> newRecursionItem;
            IterateMetadata(newRecursionItem, File, i);
            ListOfMembers.push_back(newRecursionItem);
        }

        ParseMetadata();

        // CLI_ERROR("\n\n\nTEST END");
    }
    void JsonParse::IterateMetadata(std::vector<RecursionsPerMember> &itemsVector, Json::Value &iterationFile, int count)
    {
        RecursionsPerMember newItem;
        Json::Value newFile;
        int newFileMemberSize = -1;
        int InternalCounter = 0;
        try
        {
            // CLI_WARN("1");
            newFile = iterationFile.get(iterationFile.getMemberNames()[count], "ERROR");
            // CLI_WARN("2");
            try
            {
                newFileMemberSize = (int)newFile.getMemberNames().size();
            }
            catch (Json::Exception)
            {
                // CLI_ERROR("{0}", i.what());
                newFileMemberSize = 1;
            }
            // CLI_WARN("3");
            newItem.MemberName = iterationFile.getMemberNames()[count];
            // CLI_WARN("4");
            newItem.CurrentTotalMembers = newFileMemberSize;
            // CLI_WARN("NEW MEMBER NAME = {0} | Member items = {1}", newItem.MemberName, newItem.CurrentTotalMembers);
            // CLI_INFO("NEW ITERATION:\n{0}", newFile.toStyledString());
            itemsVector.push_back(newItem);

            int nextCount = 0;
            try
            {
                nextCount = (int)newFile.getMemberNames().size();
                // CLI_INFO("next count = {0}", nextCount);
                for (int i = 0; i < nextCount; i++)
                {
                    IterateMetadata(itemsVector, newFile, i);
                }
            }
            catch (Json::Exception)
            {
                // CLI_ERROR("{0}", i.what());
                // CLI_INFO("SKIPPING COUNT.");
            }
            // IterateMetadata(itemsVector, newFile, InternalCounter);
        }
        catch (Json::Exception &i)
        {
            CLI_ERROR("{0}", i.what());
        }
    }
    void JsonParse::ParseMetadata()
    {
        AssignTypes();
    }
    void JsonParse::AssignTypes()
    {
        for (int i = 0; i < ListOfMembers.size(); i++)
        {
            for (int j = 0; j < ListOfMembers[i].size(); j++)
            {
                if (j == 0)
                {
                    ListOfMembers[i][j].Type = RecursionMemberType::Parent;
                }
                if (j != 0 && ListOfMembers[i][j].CurrentTotalMembers > 1)
                {
                    ListOfMembers[i][j].Type = RecursionMemberType::Child;
                }
                if (j != 0 && ListOfMembers[i][j].Type != RecursionMemberType::Child && ListOfMembers[i][j].CurrentTotalMembers == 1)
                {
                    ListOfMembers[i][j].Type = RecursionMemberType::ChildOfChild;
                }
                // CLI_INFO("i={0}|j={1}| name = {2}; type = {3}; total members = {4}", i, j,
                // ListOfMembers[i][j].MemberName, RecursionMemberTypeToString(ListOfMembers[i][j].Type),
                // ListOfMembers[i][j].CurrentTotalMembers);
            }
        }
    }

    /*
    void JsonParse::ProbeMemberDepth(Json::Value *root)
    {
        Json::Value temp = *root;
        std::vector<Json::String> members = temp.getMemberNames();
        for (int i = 0; i < depth; i++)
        {
            temp = temp.get(members[0], "ERROR");
            members = temp.getMemberNames();
        }
        CLI_INFO("{0}", temp.toStyledString());
        int member_count = 0;
        for (int i = 0; i < members.size(); i++)
        {
            try
            {
                CLI_WARN("{0} MEMBER = {1}", i + 1, members[i]);
                member_count = temp.get(members[i], "ERROR").size();
            }
            catch (Json::Exception &i)
            {
                CLI_ERROR("MEMBER FAILED {0}", i.what());
                break;
            }
            CLI_ERROR("MEMBER HAS SIZE = {0}", member_count);
            total_members.push_back(std::make_tuple(i, member_count, members[i]));

            // CLI_INFO("{0}", temp.get("abilityscores", "ERROR").get("charisma", "ERROR").get("base", "ERROR").asString());
            // CLI_INFO("{0}", temp.get(members[i], "ERROR").asString());
        }
    }
    */
    /*
    void JsonParse::ProbeMemberChildren(Json::Value *root)
    {
        // CLI_TRACE("START HERE");
        Json::Value temp = *root;
        Json::Value next = temp;
        std::vector<Json::String> members = temp.getMemberNames();
        std::vector<Json::String> next_members;
        for (int i = 0; i < depth; i++)
        {
            temp = temp.get(members[0], "ERROR");
            members = temp.getMemberNames();
        }
        // int member_count = 0;
        for (int i = 0; i < temp.getMemberNames().size(); i++)
        {
            // CLI_INFO("{0} member size = {1}", i, temp.getMemberNames().size());
            try
            {
                next = temp.get(members[i], "ERROR");
                // CLI_WARN("{0}", next.toStyledString());
                if (next.get(next.getMemberNames()[0], "ERROR").type() == Json::ValueType::objectValue)
                {
                    next_members = next.getMemberNames();
                    for (int j = 0; j < next_members.size(); j++)
                    {
                        try
                        {
                            // CLI_WARN("{0} MEMBER = {1}", j + 1, next_members[j]);
                            //  member_count = next.get(next_members[i], "ERROR").size();
                            // member_count = i;
                            // CLI_ERROR("MEMBER HAS SIZE = {0}", member_count);
                            member_children.push_back(std::make_tuple(j, i, next_members[j]));
                        }
                        catch (Json::Exception)
                        {
                            // CLI_ERROR("INNER CATCH MEMBER FAILED {0}", k.what());
                            break;
                        }
                    }
                }
            }
            catch (Json::Exception)
            {
                // CLI_ERROR("OUTER CATCH MEMBER FAILED {0}", q.what());
            }
        }
    }
    */
    /*
     void JsonParse::ProbeDepthAndMembers(Json::Value *root)
     {
         Json::Value temp = *root;
         Json::Value prev;
         std::vector<Json::String> members;
         // std::vector<Json::String> members2 = temp.getMemberNames();

         int count = 0;
         while (true)
         {
             members = temp.getMemberNames();
             // CLI_TRACE("MEMBERS SIZE = {0}", members.size());
             if (members.size() == 1 && temp.get(members[0], "ERROR") != "ERROR")
             {
                 // CLI_ERROR("{0}", members[0]);
                 temp = temp.get(members[0], "ERROR");
                 try
                 {
                     members = temp.getMemberNames();
                     // CLI_INFO("member = {0}", members[0]);

                     // CLI_INFO("member = {0}", temp.getMemberNames()[0]);
                 }
                 catch (Json::Exception &i)
                 {
                     CLI_ERROR("MEMBER FAILED {0}", i.what());
                     // CLI_ERROR("COUNT = {0}", count);

                     // total_members = members;
                     depth = count;

                     temp = *root;
                     members = temp.getMemberNames();
                     for (int i = 0; i < depth; i++)
                     {
                         // CLI_WARN("i = {0}, depth = {1}", i, depth);
                         temp = temp.get(members[0], "ERROR");
                         members = temp.getMemberNames();
                     }

                     break;
                 }
                 count++;
             }
             else
             {
                 break;
             }
         }
         // CLI_WARN("{0}", temp.toStyledString());
         int member_count = 0;
         for (int i = 0; i < members.size(); i++)
         {
             try
             {
                 // CLI_WARN("{0} MEMBER = {1}", i + 1, members[i]);
                 member_count = temp.get(members[i], "ERROR").size();
             }
             catch (Json::Exception &i)
             {
                 CLI_ERROR("MEMBER FAILED {0}", i.what());
                 break;
             }
             // CLI_ERROR("MEMBER HAS SIZE = {0}", member_count);
             total_members.push_back(std::make_tuple(i, member_count, members[i]));
         }

         // total_members = members;
         depth = count;
     }*/

}