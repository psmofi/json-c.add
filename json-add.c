#include <json/json.h>
#include <stdio.h>

void test_parse_obj_to_string(struct json_object* const obj) {
    json_object_object_foreach(obj, key, val) {
        printf("-- \t%s: %s\n", key, json_object_to_json_string(val));
    }
}

void test_parse_check_type(struct json_object* const obj) {
    json_object_object_foreach(obj, key, val) {
        if (json_object_is_type(val, json_type_null)) {
            printf("-- \tjson_type_null -> \t%s: %s\n",
                    key, json_object_to_json_string(val));
        }
        if (json_object_is_type(val, json_type_boolean)) {
            printf("-- \tjson_type_boolean -> \t%s: %s\n",
                    key, json_object_to_json_string(val));
            printf("-- \t\tvalue: %s\n", json_object_get_boolean(val)? "true": "false");
        }
        if (json_object_is_type(val, json_type_double)) {
            printf("-- \tjson_type_double -> \t%s: %s\n",
                    key, json_object_to_json_string(val));
            printf("-- \t\tvalue: %lf\n", json_object_get_double(val));
        }
        if (json_object_is_type(val, json_type_int)) {
            printf("-- \tjson_type_int -> \t%s: %s\n",
                    key, json_object_to_json_string(val));
            printf("-- \t\tvalue: %d\n", json_object_get_int(val));
        }
        if (json_object_is_type(val, json_type_object)) {
            printf("-- \tjson_type_object -> \t%s: %s\n",
                    key, json_object_to_json_string(val));
            printf(">>> START object \n");
            test_parse_check_type(val);
            printf("<<< END object \n");
        }
        if (json_object_is_type(val, json_type_array)) {
            printf("-- \tjson_type_array -> \t%s: %s\n",
                    key, json_object_to_json_string(val));

            for (int i = 0; i < json_object_array_length(val); ++i) {
                struct json_object *a = json_object_array_get_idx(val, i);
                printf("-- \t\tvalue: [%d]=%s\n", i, json_object_to_json_string(a));
            }
        }
        if (json_object_is_type(val, json_type_string)) {
            printf("-- \tjson_type_object -> \t%s: %s\n",
                    key, json_object_to_json_string(val));
            printf("-- \t\tvalue: %s\n", json_object_get_string(val));
        }
    }
}


//エアコンのファイル内の温度を変更するサンプル
int main() {
  //もらってきたデータ
  int hoge = 10;

  json_object *jobj = json_object_from_file("./config.json");
  //json_object * jobj = json_object_new_object();

  // json形式でのint jint = 10;
  json_object *jint = json_object_new_int(hoge);

  // jobjオブジェクト内の"Number of posts"に10を代入
  json_object_object_add(jobj,"Number of posts", jint);

  //JSONファイルを吐き出す
  test_parse_obj_to_string(jobj);

}
